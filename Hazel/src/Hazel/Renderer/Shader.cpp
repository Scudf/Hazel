#include "hzpch.h"
#include "Hazel/Renderer/Shader.h"

#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
	////////////////////////////////////////////////////////////////////
	// Shader //////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE: HZ_CORE_ASSERT(false, "ERenderer::NONE currently not implemented!") return nullptr;
		case RendererAPI::API::OPEN_GL: return MakeRef<OpenGLShader>(filepath);
		}

		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::NONE: HZ_CORE_ASSERT(false, "ERenderer::NONE currently not implemented!") return nullptr;
			case RendererAPI::API::OPEN_GL: return MakeRef<OpenGLShader>(name, vertexSource, fragmentSource);
		}

		return nullptr;
	}

	////////////////////////////////////////////////////////////////////
	// ShaderLibrary ///////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader)
	{
		HZ_CORE_ASSERT(!exists(name), "Shader already exists!");
		m_shaders[name] = shader;
	}

	void ShaderLibrary::add(const Ref<Shader>& shader)
	{
		add(shader->getName(), shader);
	}

	Ref<Shader> ShaderLibrary::load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		add(shader);

		return shader;
	}

	Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		add(shader->getName(), shader);

		return shader;
	}

	Ref<Shader> ShaderLibrary::get(const std::string& name)
	{
		HZ_CORE_ASSERT(exists(name), "Shader not found!");
		return m_shaders[name];
	}

	bool ShaderLibrary::exists(const std::string& name) const
	{
		return m_shaders.find(name) != m_shaders.end();
	}
}
