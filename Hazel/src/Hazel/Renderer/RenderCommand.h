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
		static void Init()
		{
			m_rendererAPI->init();
		}
		
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			m_rendererAPI->setViewport(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4& color)
		{
			m_rendererAPI->setClearColor(color);
		}

		static void Clear()
		{
			m_rendererAPI->clear();
		}

		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			m_rendererAPI->drawIndexed(vertexArray);
		}
	};
}
