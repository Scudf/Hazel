#include "hzpch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Hazel
{
	Application::Application()
	{
		m_window = std::unique_ptr<Window>(Window::Create());
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
}
