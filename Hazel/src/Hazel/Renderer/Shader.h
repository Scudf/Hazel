#pragma once

#include <string>

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
	};
}
