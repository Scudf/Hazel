#include "hzpch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Hazel
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->setEventCallback(BIND_EVENT_FN(onEvent));
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (m_running)
		{
			m_window->onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		HZ_CORE_TRACE("{0}", e);

		EventDispatcher eventDispatcher(e);
		eventDispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}
}
