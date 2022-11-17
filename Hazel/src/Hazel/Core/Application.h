#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Core/Window.h"
#include "Hazel/Core/LayerStack.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"

namespace Hazel
{
	class Application
	{
	private:
		static Application* s_instance;

		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_imGuiLayer = nullptr;

		bool m_running = true;
		bool m_minimized = false;
		LayerStack m_layerStack;

		float m_lastFrameTime = 0.0f;

		bool onWindowClosed(WindowCloseEvent& e);
		bool onWindowResized(WindowResizeEvent& e);
	public:
		static Application& Get() { return *s_instance; }

		Application();
		virtual ~Application();

		void run();
		void update();
		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		Window& getWindow() { return *m_window; }
	};

	// to be defined in CLIENT
	Application* CreateApplication();
}
