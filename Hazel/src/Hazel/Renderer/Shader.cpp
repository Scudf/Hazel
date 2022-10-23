#include "hzpch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Hazel
{
	unsigned int Shader::Create(int type, const std::string& shaderSource)
	{
		unsigned int shaderID = glCreateShader(type);

		// Send the shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const char* source = shaderSource.c_str();
		glShaderSource(shaderID, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(shaderID);

		int isCompiled = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			char* infoLog = (char*)alloca(maxLength * sizeof(char));
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(shaderID);

			// Use the infoLog as you see fit.
			HZ_CORE_ERROR("{0}", infoLog);
			HZ_CORE_ASSERT(false, "Vertex shader compilation failure!");

			// In this simple program, we'll just leave
			return 0;
		}

		return shaderID;
	}

	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		// Create an empty vertex shader handle
		unsigned int vertexShader = Create(GL_VERTEX_SHADER, vertexSource);

		// Create an empty fragment shader handle
		unsigned int fragmentShader = Create(GL_FRAGMENT_SHADER, fragmentSource);

		if (vertexShader && !fragmentShader)
			glDeleteShader(vertexShader);

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_programID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_programID, vertexShader);
		glAttachShader(m_programID, fragmentShader);

		// Link our program
		glLinkProgram(m_programID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		int isLinked = 0;
		glGetProgramiv(m_programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			char* infoLog = (char*)alloca(maxLength * sizeof(char));
			glGetProgramInfoLog(m_programID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_programID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			HZ_CORE_ERROR("{0}", infoLog);
			HZ_CORE_ASSERT(false, "Shader link failure!");

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_programID, vertexShader);
		glDetachShader(m_programID, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_programID);
	}

	void Shader::bind() const
	{
		glUseProgram(m_programID);
	}

	void Shader::unbind() const
	{
		glUseProgram(0);
	}
}
