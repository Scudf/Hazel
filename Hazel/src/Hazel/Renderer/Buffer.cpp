#include "hzpch.h"
#include "Buffer.h"

#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel
{
	VertexBuffer* VertexBuffer::Create(float* vertices, int64_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE: HZ_CORE_ASSERT(false, "ERenderer::NONE currently not implemented!") return nullptr;
		case RendererAPI::API::OPEN_GL: return new OpenGLVertexBuffer(vertices, size);
		}

		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, int count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE: HZ_CORE_ASSERT(false, "ERenderer::NONE currently not implemented!") return nullptr;
		case RendererAPI::API::OPEN_GL: return new OpenGLIndexBuffer(indices, count);
		}

		return nullptr;
	}
}
