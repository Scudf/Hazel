#pragma once

#include <string>

namespace Hazel
{
	class Shader
	{
	public:
		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource);

		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};
}
