#pragma once

#include "Hazel/Renderer/Buffer.h"

namespace Hazel
{
	class OpenGLVertexBuffer
		: public VertexBuffer
	{
	private:
		uint32_t m_bufferID = 0;
		BufferLayout m_layout;

	public:
		OpenGLVertexBuffer(float* vertices, int64_t size);
		~OpenGLVertexBuffer() override;

		void bind() const override;
		void unbind() const override;

		virtual const BufferLayout& getLayout() const override { return m_layout; }
		virtual void setLayout(const BufferLayout& layout) { m_layout = layout; }
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
