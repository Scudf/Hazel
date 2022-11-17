#include "hzpch.h"

#include "WindowsWindow.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Hazel
{
	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	void WindowsWindow::init(const WindowProps& props)
	{
		HZ_PROFILE_FUNCTION();

		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (s_GLFWWindowCount == 0)
		{
			HZ_CORE_INFO("Initializing GLFW");
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			HZ_PROFILE_SCOPE("glfwCreateWindow");

			m_window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		m_context = MakeScope<OpenGLContext>(m_window);
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

				WindowResizeEvent e(width, height);
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
					KeyPressEvent e(key, 0);
					data.callback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleaseEvent e(key);
					data.callback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressEvent e(key, 1);
					data.callback(e);
					break;
				}
				}
			});

		glfwSetCharCallback(m_window,
			[](GLFWwindow* window, uint32_t keyCode)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypeEvent e(keyCode);
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
					MouseButtonPressEvent e(button);
					data.callback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleaseEvent e(button);
					data.callback(e);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_window,
			[](GLFWwindow* window, double xpos, double ypos)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrollEvent e((float)xpos, (float)ypos);
				data.callback(e);
			});

		glfwSetCursorPosCallback(m_window,
			[](GLFWwindow* window, double xpos, double ypos)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMoveEvent e((float)xpos, (float)ypos);
				data.callback(e);
			});
	}

	void WindowsWindow::shutdown()
	{
		HZ_PROFILE_FUNCTION();

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
		HZ_PROFILE_FUNCTION();

		glfwPollEvents();
		m_context->swapBuffers();
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		HZ_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.VSync = enabled;
	}
}
