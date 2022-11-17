#include "hzpch.h"
#include "Hazel/Renderer/Texture.h"

#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Hazel
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE: HZ_CORE_ASSERT(false, "ERenderer::NONE currently not implemented!") return nullptr;
		case RendererAPI::API::OPEN_GL: return MakeRef<OpenGLTexture2D>(width, height);
		}

		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::NONE: HZ_CORE_ASSERT(false, "ERenderer::NONE currently not implemented!") return nullptr;
			case RendererAPI::API::OPEN_GL: return MakeRef<OpenGLTexture2D>(path);
		}

		return nullptr;
	}
}