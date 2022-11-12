#pragma once

#include <glm/glm.hpp>

#include "Hazel/Renderer/Shader.h"

typedef uint32_t GLenum;

namespace Hazel
{
	using ShaderSourcesUMap_t = std::unordered_map<GLenum, std::string>;

	class OpenGLShader
		: public Shader
	{
	private:
		uint32_t m_programID = 0;
		std::string m_name;

		std::string readFile(const std::string& filepath);
		ShaderSourcesUMap_t preProcess(const std::string& source);
		void compile(const ShaderSourcesUMap_t& shaderSources);
		std::string cutName(const std::string& filepath);

	public:
		static uint32_t Create(int type, const std::string& shaderSource);

		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader() override;

		void bind() const override;
		void unbind() const override;

		void uploadUniformInt(const std::string& name, int value);

		void uploadUniformFloat(const std::string& name, float value);
		void uploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void uploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void uploadUniformFloat4(const std::string& name, const glm::vec4& values);

		void uploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		const std::string& getName() const override { return m_name; }
	};
}
