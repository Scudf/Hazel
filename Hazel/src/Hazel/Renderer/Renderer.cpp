#include "hzpch.h"
#include "Hazel/Renderer/Renderer.h"

#include "Hazel/Renderer/Renderer2D.h"

namespace Hazel
{
	Scope<Renderer::SceneData> Renderer::m_sceneData = MakeScope<SceneData>();

	void Renderer::Init()
	{
		HZ_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResized(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(const OrthographicCamera& camera)
	{
		m_sceneData->viewProjection = camera.getViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(
		const Ref<Shader>& shader,
		const Ref<VertexArray>& vertexArray,
		const glm::mat4& transform)
	{
		shader->bind();
		shader->setMat4("u_ViewProjection", m_sceneData->viewProjection);
		shader->setMat4("u_Transform", transform);

		vertexArray->bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}