#pragma once

#include <glad/glad.h>

#include "Hazel/Renderer/Texture.h"

namespace Hazel
{
	class OpenGLTexture2D
		: public Texture2D
	{
	private:
		enum ColorChannels
		{
			RGB = 3,
			RGBA = 4
		};

		std::string m_path;
		uint32_t m_width, m_height, m_textureID;
		GLenum m_dataFormat = 0, m_internalFormat = 0;

		void initFormats(ColorChannels channels = RGBA);
		void init();

	public:
		OpenGLTexture2D(uint32_t width = 1, uint32_t height = 1);
		OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D() override;

		void bind(uint32_t slot = 0) const override;
		void unbind(uint32_t slot = 0) const override;

		void setData(void* data, uint32_t size) override;

		uint32_t getWidth() const override  { return m_width; }
		uint32_t getHeight() const override  { return m_height; }
	};
}
