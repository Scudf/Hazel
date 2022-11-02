#include "hzpch.h"
#include "Renderer.h"

#include <glad/glad.h>

namespace Hazel
{
	Renderer::SceneData* Renderer::m_sceneData = new SceneData();

	void Renderer::BeginScene(const OrthographicCamera& camera)
	{
		m_sceneData->viewProjection = camera.getViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->bind();
		shader->uploadUniformMat4("u_ViewProjection", m_sceneData->viewProjection);

		vertexArray->bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}