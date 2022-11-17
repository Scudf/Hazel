#include "hzpch.h"
#include "Hazel/Renderer/GraphicsContext.h"

#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Hazel
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OPEN_GL:  return MakeScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
