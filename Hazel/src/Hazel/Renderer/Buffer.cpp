#include "hzpch.h"
#include "Hazel/Renderer/Buffer.h"

#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, int64_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE: HZ_CORE_ASSERT(false, "ERenderer::NONE currently not implemented!") return nullptr;
		case RendererAPI::API::OPEN_GL: return MakeRef<OpenGLVertexBuffer>(vertices, size);
		}

		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, int count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE: HZ_CORE_ASSERT(false, "ERenderer::NONE currently not implemented!") return nullptr;
		case RendererAPI::API::OPEN_GL: return MakeRef<OpenGLIndexBuffer>(indices, count);
		}

		return nullptr;
	}
}
