#pragma once

#include "glm/glm.hpp"

#include "Hazel/Renderer/VertexArray.h"

namespace Hazel
{
	class RendererAPI
	{
	public:
		enum class API
		{
			NONE,
			OPEN_GL
		};

		static API GetAPI() { return s_API; };
		static Scope<RendererAPI> Create();

		virtual void init() = 0;
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void setClearColor(const glm::vec4& color) = 0;
		virtual void clear() = 0;

		virtual void drawIndexed(const Ref<VertexArray> vertexArray) = 0;

	private:
		static API s_API;
	};
}
