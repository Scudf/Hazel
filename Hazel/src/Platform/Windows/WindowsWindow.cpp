#include "hzpch.h"

#include "WindowsWindow.h"

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
        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, &m_data);
        setVSync(true);
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
        glfwSwapBuffers(m_window);
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
