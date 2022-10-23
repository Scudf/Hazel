#pragma once

#include "Hazel/Renderer/Buffer.h"

namespace Hazel
{
	class OpenGLVertexBuffer
		: public VertexBuffer
	{
	private:
		uint32_t m_bufferID = 0;

	public:
		OpenGLVertexBuffer(float* vertices, int64_t size);
		~OpenGLVertexBuffer() override;

		void bind() const override;
		void unbind() const override;
	};

	class OpenGLIndexBuffer
		: public IndexBuffer
	{
	private:
		uint32_t m_bufferID = 0;
		uint32_t m_count = 0;

	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer() override;

		void bind() const override;
		void unbind() const override;

		uint32_t getCount() const override { return m_count; }
	};
}
