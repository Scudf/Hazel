#include "hzpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

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
		HZ_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_window);
		uint32_t status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		HZ_CORE_INFO("Open GL info:");
		HZ_CORE_INFO("  Vendor: {0}",	(const char*)glGetString(GL_VENDOR));
		HZ_CORE_INFO("  Renderer: {0}",	(const char*)glGetString(GL_RENDERER));
		HZ_CORE_INFO("  Version: {0}",	(const char*)glGetString(GL_VERSION));

#ifdef HZ_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		HZ_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Hazel requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::swapBuffers()
	{
		HZ_PROFILE_FUNCTION();

		glfwSwapBuffers(m_window);
	}
}
