#include "hzpch.h"

#include "WindowsWindow.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Hazel
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	void WindowsWindow::init(const WindowProps& props)
	{
		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
		
		m_context = new OpenGLContext(m_window);
		m_context->init();

		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);

		// set event callbacks
		glfwSetWindowSizeCallback(m_window,
			[](GLFWwindow* window, int width, int height)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				WindowResizedEvent e(width, height);
				data.callback(e);
			});

		glfwSetWindowCloseCallback(m_window,
			[](GLFWwindow* window)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent e;
				data.callback(e);
			});

		glfwSetKeyCallback(m_window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key, 0);
					data.callback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					data.callback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent e(key, 1);
					data.callback(e);
					break;
				}
				}
			});

		glfwSetCharCallback(m_window,
			[](GLFWwindow* window, uint32_t keyCode)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent e(keyCode);
				data.callback(e);
			});

		glfwSetMouseButtonCallback(m_window,
			[](GLFWwindow* window, int button, int action, int mods)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(button);
					data.callback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(button);
					data.callback(e);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_window,
			[](GLFWwindow* window, double xpos, double ypos)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent e((float)xpos, (float)ypos);
				data.callback(e);
			});

		glfwSetCursorPosCallback(m_window,
			[](GLFWwindow* window, double xpos, double ypos)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent e((float)xpos, (float)ypos);
				data.callback(e);
			});
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(m_window);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		shutdown();
	}

	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		m_context->swapBuffers();
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.VSync = enabled;
	}
}
