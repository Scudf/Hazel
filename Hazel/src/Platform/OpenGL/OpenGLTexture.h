#pragma once

#include "Hazel/Renderer/Texture.h"

namespace Hazel
{
	class OpenGLTexture2D
		: public Texture2D
	{
	private:
		std::string m_path;
		uint32_t m_width, m_height, m_textureID;

	public:
		OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D() override;

		virtual void bind(uint32_t slot = 0) const;
		virtual void unbind(uint32_t slot = 0) const;

		virtual uint32_t getWidth() const { return m_width; }
		virtual uint32_t getHeight() const { return m_height; }
	};
}
