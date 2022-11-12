#include "hzpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Hazel
{
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