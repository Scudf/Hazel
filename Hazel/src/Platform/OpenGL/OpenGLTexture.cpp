#include "hzpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Hazel
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(1);
		stbi_uc* texture = stbi_load(path.c_str(), &width, &height, &channels, 0);
		HZ_CORE_ASSERT(texture, "Failed to load image!");
		m_width = width;
		m_height = height;

		GLenum internalFormat, dataFormat;

		switch (channels)
		{
		case 4:
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;

			break;
		case 3:
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;

			break;
		default:
			HZ_CORE_ASSERT(false, "Format not supported!");
			internalFormat = 0;
			dataFormat = 0;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
		glTextureStorage2D(m_textureID, 1, internalFormat, m_width, m_height);

		glTextureParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, texture);

		stbi_image_free(texture);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_textureID);
	}

	void OpenGLTexture2D::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_textureID);
	}
}
