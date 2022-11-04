#pragma once

#include <glm/glm.hpp>

#include "Hazel/Renderer/Shader.h"

namespace Hazel
{
	class OpenGLShader
		: public Shader
	{
	private:
		uint32_t m_programID = 0;

	public:
		static unsigned int Create(int type, const std::string& shaderSource);

		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader() override;

		void bind() const override;
		void unbind() const override;

		void uploadInt(const std::string& name, int value);

		void uploadFloat(const std::string& name, float value);
		void uploadFloat2(const std::string& name, const glm::vec2& values);
		void uploadFloat3(const std::string& name, const glm::vec3& values);
		void uploadFloat4(const std::string& name, const glm::vec4& values);

		void uploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	};
}
