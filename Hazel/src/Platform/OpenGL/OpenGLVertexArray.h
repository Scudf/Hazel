#pragma once

#include <memory>

#include "Hazel/Renderer/VertexArray.h"

namespace Hazel
{
	class OpenGLVertexArray :
		public VertexArray
	{
	private:
		uint32_t m_vertedArrayID = 0;
		std::vector<Ref<VertexBuffer>> m_vertexBuffers;
		Ref<IndexBuffer> m_indexBuffer;

	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		void bind() const override;
		void unbind() const override;

		void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override { return m_vertexBuffers; };
		const Ref<IndexBuffer>& getIndexBuffer() const override { return m_indexBuffer; };
	};
}
