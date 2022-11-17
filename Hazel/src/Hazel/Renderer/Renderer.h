#pragma once

#include "Hazel/Renderer/RenderCommand.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/OrthographicCamera.h"

namespace Hazel
{
	class Renderer
	{
	private:
		struct SceneData
		{
			glm::mat4 viewProjection;
		};

		static Scope<SceneData> m_sceneData;

	public:
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void Init();
		static void Shutdown();

		static void OnWindowResized(uint32_t width, uint32_t height);

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Submit(
			const Ref<Shader>& shader,
			const Ref<VertexArray>& vertexArray,
			const glm::mat4& transform = glm::mat4(1.0f));
	};
}
