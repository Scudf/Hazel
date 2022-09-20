#pragma once

#include "Core.h"
#include "Window.h"

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
	};

	// to be defined in CLIENT
	Application* CreateApplication();
}
