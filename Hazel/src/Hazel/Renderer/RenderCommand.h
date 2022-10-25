#pragma once

#include <glm/glm.hpp>

#include "RendererAPI.h"

namespace Hazel
{
	class RenderCommand
	{
	private:
		static RendererAPI* m_rendererAPI;

	public:
		static void SetClearColor(const glm::vec4& color)
		{

		}

		static void Clear()
		{

		}

		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			m_rendererAPI->drawIndexed(vertexArray);
		}
	};
}
