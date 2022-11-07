#pragma once

#include "Hazel/Renderer/RendererAPI.h"

namespace Hazel
{

	class OpenGLRendererAPI :
		public RendererAPI
	{

	public:
		void setClearColor(const glm::vec4& color) override;
		void clear() override;

		void drawIndexed(const Ref<VertexArray> vertexArray) override;
	};
}
