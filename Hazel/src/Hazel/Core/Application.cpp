#include "hzpch.h"

#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/ImGui/ImGuiLayer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Renderer/Renderer2D.h"

#include <GLFW/glfw3.h> // TO DO: platform based

namespace Hazel
{
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		HZ_PROFILE_FUNCTION();

		HZ_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->setEventCallback(HZ_BIND_EVENT_FN(Application::onEvent));

		Renderer::Init();
		Renderer2D::Init();

		m_imGuiLayer = new ImGuiLayer();
		pushOverlay(m_imGuiLayer);
	}

	Application::~Application()
	{
		HZ_PROFILE_FUNCTION();
	}

	void Application::run()
	{
		HZ_PROFILE_FUNCTION();

		while (m_running)
		{
			update();
		}
	}

	void Application::update()
	{
		HZ_PROFILE_FUNCTION();

		const float time = (float)glfwGetTime(); // TO DO: platform based
		Timestep ts = time - m_lastFrameTime;
		m_lastFrameTime = time;

		if (!m_minimized)
		{
			{
				HZ_PROFILE_SCOPE("LayerStack OnUpdate");

				for (Layer* layer : m_layerStack)
					layer->onUpdate(ts);
			}
		}

		m_imGuiLayer->begin();
		{
			HZ_PROFILE_SCOPE("LayerStack OnImGuiRender");

			for (Layer* layer : m_layerStack)
				layer->onImGUIRender();
		}
		m_imGuiLayer->end();
		m_window->onUpdate();
	}

	void Application::onEvent(Event& e)
	{
		HZ_PROFILE_FUNCTION();

		EventDispatcher eventDispatcher(e);
		eventDispatcher.dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::onWindowClosed));
		eventDispatcher.dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(Application::onWindowResized));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->onEvent(e);
			if (e.isHandled)
				break;
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		HZ_PROFILE_FUNCTION();

		m_layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* overlay)
	{
		HZ_PROFILE_FUNCTION();

		m_layerStack.pushOverlay(overlay);
	}

	bool Application::onWindowClosed(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}

	bool Application::onWindowResized(WindowResizeEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		if (e.getWidth() == 0 || e.getHeight() == 0)
		{
			m_minimized = true;
			return false;
		}

		Renderer::OnWindowResized(e.getWidth(), e.getHeight());
		update();

		m_minimized = false;
		return false;
	}
}
