#include "hzpch.h"
#include "Renderer.h"

#include <glad/glad.h>

namespace Hazel
{
	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}