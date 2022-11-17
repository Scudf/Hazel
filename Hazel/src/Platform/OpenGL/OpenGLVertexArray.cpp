#include "hzpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Hazel
{
	static uint32_t ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Hazel::ShaderDataType::FLOAT:		return GL_FLOAT;
		case Hazel::ShaderDataType::FLOAT2:		return GL_FLOAT;
		case Hazel::ShaderDataType::FLOAT3:		return GL_FLOAT;
		case Hazel::ShaderDataType::FLOAT4:		return GL_FLOAT;
		case Hazel::ShaderDataType::INT:		return GL_INT;
		case Hazel::ShaderDataType::INT2:		return GL_INT;
		case Hazel::ShaderDataType::INT3:		return GL_INT;
		case Hazel::ShaderDataType::INT4:		return GL_INT;
		case Hazel::ShaderDataType::MAT3:		return GL_FLOAT;
		case Hazel::ShaderDataType::MAT4:		return GL_FLOAT;
		case Hazel::ShaderDataType::BOOL:		return GL_BOOL;
		}

		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		HZ_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_vertedArrayID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		HZ_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_vertedArrayID);
	}

	void OpenGLVertexArray::bind() const
	{
		HZ_PROFILE_FUNCTION();

		glBindVertexArray(m_vertedArrayID);
	}

	void OpenGLVertexArray::unbind() const
	{
		HZ_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		HZ_PROFILE_FUNCTION();

		HZ_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer has no layout!");

		bind();
		vertexBuffer->bind();

		const auto& layouts = vertexBuffer->getLayout();
		uint32_t index = 0;
		for (auto& layout : layouts)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index++,
				layout.getComponentCount(),
				ShaderDataTypeToOpenGLBaseType(layout.type),
				layout.normalized,
				layouts.getStride(),
				(const void*)(uint64_t)layout.offset);
		}

		m_vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		HZ_PROFILE_FUNCTION();

		bind();
		indexBuffer->bind();

		m_indexBuffer = indexBuffer;
	}
}
