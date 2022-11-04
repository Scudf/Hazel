#pragma once

#include <cstdint>

namespace Hazel
{
	enum class ShaderDataType
	{
		NONE,
		FLOAT,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		INT,
		INT2,
		INT3,
		INT4,
		MAT3,
		MAT4,
		BOOL
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::FLOAT:		return 4;
			case ShaderDataType::FLOAT2:	return 4 * 2;
			case ShaderDataType::FLOAT3:	return 4 * 3;
			case ShaderDataType::FLOAT4:	return 4 * 4;
			case ShaderDataType::INT:		return 4;
			case ShaderDataType::INT2:		return 4 * 2;
			case ShaderDataType::INT3:		return 4 * 3;
			case ShaderDataType::INT4:		return 4 * 4;
			case ShaderDataType::MAT3:		return 4 * 3 * 3;
			case ShaderDataType::MAT4:		return 4 * 4 * 4;
			case ShaderDataType::BOOL:		return 1;
		}

		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string name;
		ShaderDataType type = ShaderDataType::NONE;
		uint32_t size = 0;
		uint32_t offset = 0;
		bool normalized = false;

		BufferElement() {}
		BufferElement(ShaderDataType l_type, const std::string& l_name, bool l_normalized = false)
			: type(l_type), name(l_name), size(ShaderDataTypeSize(l_type)), normalized(l_normalized) { }

		uint32_t getComponentCount() const
		{
			switch (type)
			{
				case ShaderDataType::FLOAT:		return 1;
				case ShaderDataType::FLOAT2:	return 2;
				case ShaderDataType::FLOAT3:	return 3;
				case ShaderDataType::FLOAT4:	return 4;
				case ShaderDataType::INT:		return 1;
				case ShaderDataType::INT2:		return 2;
				case ShaderDataType::INT3:		return 3;
				case ShaderDataType::INT4:		return 4;
				case ShaderDataType::MAT3:		return 3 * 3;
				case ShaderDataType::MAT4:		return 4 * 4;
				case ShaderDataType::BOOL:		return 1;
			}

			HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	using layout_it = std::vector<BufferElement>::iterator;
	using layout_const_it = std::vector<BufferElement>::const_iterator;

	class BufferLayout
	{
	private:
		std::vector<BufferElement> m_layouts;
		uint32_t m_stride = 0;

		void calculateOffsetAndStride()
		{
			uint32_t offset = 0;
			m_stride = 0;

			for (auto& layout : m_layouts)
			{
				layout.offset = offset;
				offset += layout.size;
				m_stride += layout.size;
			}
		}

	public:
		BufferLayout() { }
		BufferLayout(const std::initializer_list<BufferElement>& layouts)
			: m_layouts(layouts)
		{
			calculateOffsetAndStride();
		}

		const std::vector<BufferElement>& getElements() const { return m_layouts; }
		uint32_t getStride() const { return m_stride; }

		layout_it begin() { return m_layouts.begin(); }
		layout_it end() { return m_layouts.end(); }
		layout_const_it begin() const { return m_layouts.begin(); }
		layout_const_it end() const { return m_layouts.end(); }
	};

	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(float* vertices, int64_t size);

		virtual ~VertexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const BufferLayout& getLayout() const = 0;
		virtual void setLayout(const BufferLayout& layout) = 0;
	};

	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(uint32_t* indices, int count);

		virtual ~IndexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t getCount() const = 0;
	};
}
