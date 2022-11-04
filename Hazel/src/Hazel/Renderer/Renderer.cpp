#include "hzpch.h"
#include "Renderer.h"

#include <glad/glad.h>

#include "Platform/OpenGL/OpenGLShader.h"

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

	void Renderer::Submit(
		const std::shared_ptr<Shader>& shader,
		const std::shared_ptr<VertexArray>& vertexArray,
		const glm::mat4& transform)
	{
		shader->bind();
		((OpenGLShader*)shader.get())->uploadUniformMat4("u_ViewProjection", m_sceneData->viewProjection);
		((OpenGLShader*)shader.get())->uploadUniformMat4("u_Transform", transform);

		vertexArray->bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}