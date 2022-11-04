#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Hazel
{
	class Shader
	{
	private:
		uint32_t m_programID = 0;

	public:
		static unsigned int Create(int type, const std::string& shaderSource);

		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void bind() const;
		void unbind() const;

		void uploadFloat4(const std::string& name, const glm::vec4& values);
		void uploadUniformMat4(const std::string& name, const glm::mat4& viewProjection);
	};
}
