#pragma once

#include "RenderCommand.h"
#include "Shader.h"
#include "OrthographicCamera.h"

namespace Hazel
{
	class Renderer
	{
	private:
		struct SceneData
		{
			glm::mat4 viewProjection;
		};

		static SceneData* m_sceneData;

	public:
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void Init();
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Submit(
			const Ref<Shader>& shader,
			const Ref<VertexArray>& vertexArray,
			const glm::mat4& transform = glm::mat4(1.0f));
	};
}
