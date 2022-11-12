#include "hzpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE: HZ_CORE_ASSERT(false, "ERenderer::NONE currently not implemented!") return nullptr;
		case RendererAPI::API::OPEN_GL: return MakeRef<OpenGLShader>(filepath);
		}

		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::NONE: HZ_CORE_ASSERT(false, "ERenderer::NONE currently not implemented!") return nullptr;
			case RendererAPI::API::OPEN_GL: return MakeRef<OpenGLShader>(vertexSource, fragmentSource);
		}

		return nullptr;
	}
}
