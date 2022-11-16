#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Hazel
{
	class Shader
	{
	public:
		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);

		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setInt(const std::string& name, int value) = 0;
		virtual void setFloat2(const std::string& name, const glm::vec2& values) = 0;
		virtual void setFloat3(const std::string& name, const glm::vec3& values) = 0;
		virtual void setFloat4(const std::string& name, const glm::vec4& values) = 0;
		virtual void setMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void setMat4(const std::string& name, const glm::mat4& matrix) = 0;

		virtual const std::string& getName() const = 0;
	};

	class ShaderLibrary
	{
	private:
		std::unordered_map<std::string, Ref<Shader>> m_shaders;

	public:
		void add(const std::string& name, const Ref<Shader>& shader);
		void add(const Ref<Shader>& shader);

		Ref<Shader> load(const std::string& filepath);
		Ref<Shader> load(const std::string& name, const std::string& filepath);

		Ref<Shader> get(const std::string& name);

		bool exists(const std::string& name) const;
	};
}
