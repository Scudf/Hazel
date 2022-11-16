#include "hzpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

namespace Hazel
{
	void OpenGLTexture2D::initFormats(ColorChannels channels)
	{
		switch (channels)
		{
		case RGBA:
			m_internalFormat = GL_RGBA8;
			m_dataFormat = GL_RGBA;

			break;
		case RGB:
			m_internalFormat = GL_RGB8;
			m_dataFormat = GL_RGB;

			break;
		default:
			HZ_CORE_ASSERT(false, "Format not supported!");
		}
	}

	void OpenGLTexture2D::init()
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
		glTextureStorage2D(m_textureID, 1, m_internalFormat, m_width, m_height);

		glTextureParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_width(width), m_height(height), m_dataFormat(GL_RGBA)
	{
		initFormats();
		init();

		uint32_t texture = 0xffffffff;
		setData(&texture, sizeof(uint32_t));
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(1);
		stbi_uc* texture = stbi_load(path.c_str(), &width, &height, &channels, 0);
		HZ_CORE_ASSERT(texture, "Failed to load image!");
		m_width = width;
		m_height = height;

		initFormats((ColorChannels)channels);
		init();

		setData(texture, m_width * m_height * channels);
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

	void OpenGLTexture2D::unbind(uint32_t slot) const
	{
		glBindTextureUnit(slot, 0);
	}

	void OpenGLTexture2D::setData(void* data, uint32_t size)
	{
		const auto bpc = m_dataFormat == GL_RGBA ? RGBA : RGB; // bits per channel
		HZ_CORE_ASSERT(size == m_width * m_height * bpc, "Data must be entire texture");
		glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
	}
}
