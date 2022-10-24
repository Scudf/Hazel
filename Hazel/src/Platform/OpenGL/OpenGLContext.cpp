#include "hzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Hazel
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_window(windowHandle)
	{
		HZ_CORE_ASSERT(windowHandle, "Window is nullptr!");
	}

	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(m_window);
		unsigned int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		HZ_CORE_INFO("Open GL info:");
		HZ_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		HZ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		HZ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}