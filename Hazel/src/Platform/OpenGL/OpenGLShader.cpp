#include "hzpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Hazel
{
	unsigned int OpenGLShader::Create(int type, const std::string& shaderSource)
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

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
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

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_programID);
	}

	void OpenGLShader::bind() const
	{
		glUseProgram(m_programID);
	}

	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::uploadInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::uploadFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::uploadFloat2(const std::string& name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::uploadFloat3(const std::string& name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::uploadFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::uploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
