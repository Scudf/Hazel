#pragma once

#include <string>

#include "Hazel/Core/Core.h"

namespace Hazel
{

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void bind(uint32_t slot = 0) const = 0;
		virtual void unbind(uint32_t slot = 0) const = 0;

		virtual void setData(void* data, uint32_t size) = 0;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;
	};

	class Texture2D
		: public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width = 1, uint32_t height = 1);
		static Ref<Texture2D> Create(const std::string& path);
	};
}
