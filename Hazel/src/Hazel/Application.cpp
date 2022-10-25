#include "hzpch.h"

#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Hazel/Renderer/Renderer.h"

namespace Hazel
{
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->setEventCallback(HZ_BIND_EVENT_FN(Application::onEvent));

		m_imGuiLayer = new ImGuiLayer();
		pushOverlay(m_imGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (m_running)
		{
			for (Layer* layer : m_layerStack)
				layer->onUpdate();

			m_imGuiLayer->begin();
			for (Layer* layer : m_layerStack)
				layer->onRender();
			m_imGuiLayer->end();

			m_window->onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher eventDispatcher(e);
		eventDispatcher.dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::onWindowClose));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->onEvent(e);
			if (e.isHandled)
				break;
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* overlay)
	{
		m_layerStack.pushOverlay(overlay);
		overlay->onAttach();
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}
}
