#pragma once

#include <glm/glm.hpp>

#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Renderer/Texture.h"

namespace Hazel
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position,
			float rotation,
			const glm::vec2& scale,
			const glm::vec4& color = glm::vec4(1.0f),
			const Ref<Texture2D>& texture = Texture2D::Create(),
			float wrap = 1.0f);

		static void DrawQuad(
			const glm::vec3& position,
			const glm::vec3& rotation,
			const glm::vec3& scale,
			const glm::vec4& color = glm::vec4(1.0f),
			const Ref<Texture2D>& texture = Texture2D::Create(),
			const glm::vec2& wrap = glm::vec2(1.0f));
	};
}
