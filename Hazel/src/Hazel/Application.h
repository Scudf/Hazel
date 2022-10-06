#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	private:
		std::unique_ptr<Window> m_window;
		bool m_running = true;

	public:
		Application();
		virtual ~Application();

		void run();
		void onEvent(Event& e);
		bool onWindowClose(WindowCloseEvent& e);
	};

	// to be defined in CLIENT
	Application* CreateApplication();
}
