#pragma once

#include <cstdint>

namespace Hazel
{
	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(float* vertices, int64_t size);

		virtual ~VertexBuffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};

	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(uint32_t* indices, int count);

		virtual ~IndexBuffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t getCount() const = 0;
	};
}
