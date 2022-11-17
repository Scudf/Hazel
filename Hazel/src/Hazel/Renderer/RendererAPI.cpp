#include "hzpch.h"
#include "Hazel/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OPEN_GL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::NONE:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OPEN_GL:  return MakeScope<OpenGLRendererAPI>();
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
