#pragma once

#include <GLFW/glfw3.h>

#include "Hazel/Window.h"
#include "Hazel/Renderer/GraphicsContext.h"

namespace Hazel
{
	class WindowsWindow
		: public Window
	{
	private:
		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool VSync;

			EventCallbackFn callback;
		};

		GLFWwindow* m_window = nullptr;
		WindowData m_data;
		GraphicsContext* m_context = nullptr;

		virtual void init(const WindowProps& props);
		virtual void shutdown();

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void onUpdate() override;

		unsigned getWidth() const override { return m_data.width; }
		unsigned getHeight() const override { return m_data.height; }

		void setEventCallback(const EventCallbackFn& callback) override { m_data.callback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override { return m_data.VSync; };

		void* getNativeWindow() const override { return m_window; }
	};
}
