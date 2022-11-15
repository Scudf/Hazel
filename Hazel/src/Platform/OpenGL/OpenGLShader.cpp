#include "hzpch.h"
#include "OpenGLShader.h"

#include <fstream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#pragma warning(disable : HAZEL_MEMORY_DISABLED_WARNINGS)

namespace Hazel
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		else if (type == "fragment" || "pixel")
			return GL_FRAGMENT_SHADER;

		HZ_CORE_ASSERT(false, "Shader type not supported!");
		return 0;
	}

	uint32_t OpenGLShader::Create(int type, const std::string& shaderSource)
	{
		uint32_t shaderID = glCreateShader(type);

		auto source = shaderSource.c_str();
		glShaderSource(shaderID, 1, &source, 0);

		glCompileShader(shaderID);

		int isCompiled = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			auto infoLog = (char*)alloca(maxLength * sizeof(char));
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shaderID);

			HZ_CORE_ERROR("{0}", infoLog);
			HZ_CORE_ASSERT(false, "Vertex shader compilation failure!");

			return 0;
		}

		return shaderID;
	}

	std::string OpenGLShader::readFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);

		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
			HZ_CORE_ERROR("Could not open file '{0}'", filepath);

		return result;
	}

	ShaderSourcesUMap_t OpenGLShader::preProcess(const std::string& source)
	{
		ShaderSourcesUMap_t shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos); // End of shader type declaration line
			HZ_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1; // Start of shader type name (after "#type " keyword)
			std::string type = source.substr(begin, eol - begin);
			HZ_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); // Start of shader code after shader type declaration line
			HZ_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos); // Start of next shader type declaration line

			shaderSources[ShaderTypeFromString(type)] =
				(pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::compile(const ShaderSourcesUMap_t& shaderSources)
	{
		uint32_t programID = glCreateProgram();

		auto shaderIDs = (uint32_t*)alloca(shaderSources.size() * sizeof(uint32_t));
		int shaderID_index = 0;

		for (auto& type : shaderSources)
		{
			auto shader = Create(type.first, type.second);

			if (!shader)
				continue;

			glAttachShader(programID, shader);
			shaderIDs[shaderID_index++] = programID;
		}

		glLinkProgram(programID);

		int isLinked = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

			auto infoLog = (char*)alloca(maxLength * sizeof(char));
			glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(programID);

			for (int id = 0; id < shaderID_index; ++id)
				glDeleteShader(shaderIDs[id]);

			HZ_CORE_ERROR("{0}", infoLog);
			HZ_CORE_ASSERT(false, "Shader link failure!");

			return;
		}

		for (int id = 0; id < shaderID_index; ++id)
		{
			glDetachShader(programID, shaderIDs[id]);
			glDeleteShader(shaderIDs[id]);
		}

		m_programID = programID;
	}

	std::string OpenGLShader::cutName(const std::string& filepath)
	{
		auto lastSlesh = filepath.find_last_of("/\\");
		lastSlesh = lastSlesh == std::string::npos ? 0 : lastSlesh + 1;

		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlesh : lastDot - lastSlesh;

		return filepath.substr(lastSlesh, count);
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = readFile(filepath);
		auto shaderSources = preProcess(source);
		compile(shaderSources);

		m_name = cutName(filepath);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
		: m_name(name)
	{
		ShaderSourcesUMap_t shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSource;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSource;
		compile(shaderSources);
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

	void OpenGLShader::setFloat3(const std::string& name, const glm::vec3& values)
	{
		uploadUniformFloat3(name, values);
	}

	void OpenGLShader::setFloat4(const std::string& name, const glm::vec4& values)
	{
		uploadUniformFloat4(name, values);
	}

	void OpenGLShader::setMat3(const std::string& name, const glm::mat3& matrix)
	{
		uploadUniformMat3(name, matrix);
	}

	void OpenGLShader::setMat4(const std::string& name, const glm::mat4& matrix)
	{
		uploadUniformMat4(name, matrix);
	}

	void OpenGLShader::uploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::uploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::uploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::uploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::uploadUniformFloat4(const std::string& name, const glm::vec4& values)
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
