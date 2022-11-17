#include "hzpch.h"
#include "Hazel/Renderer/VertexArray.h"

#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::NONE: HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OPEN_GL: return MakeRef<OpenGLVertexArray>();
		}
	
		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
