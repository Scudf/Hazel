#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/glm/gtc/type_ptr.hpp>

#include "Hazel/Renderer/Renderer2D.h"

Sandbox2D::Sandbox2D()
	: m_cameraController(2560.0f / 1440.0f)
{
	m_checkerboard = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::onAttach()
{

}

void Sandbox2D::onDetach()
{

}

void Sandbox2D::onUpdate(Hazel::Timestep ts)
{
	// Update
	m_cameraController.onUpdate(ts);

	// Render
	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Hazel::RenderCommand::Clear();

	Hazel::Renderer2D::BeginScene(m_cameraController.getCamera());
	Hazel::Renderer2D::DrawQuad(glm::vec2(-0.5f, 0.0f), 75.0f, glm::vec2(0.5f, 1.0f), glm::vec4(0.5f, 0.2f, 0.8f, 1.0f));
	Hazel::Renderer2D::DrawQuad(glm::vec2(0.0f, -0.5f), 90.0f, glm::vec2(1.0f, 0.5f), m_flatColor);
	Hazel::Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, -0.1f), 0.0f, glm::vec3(10.0f, 10.0f, 1.0f), glm::vec4(1.0f), m_checkerboard, 10.0f);
	Hazel::Renderer2D::EndScene();
}

void Sandbox2D::onImGUIRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Color", glm::value_ptr(m_flatColor));
	ImGui::End();
}

void Sandbox2D::onEvent(Hazel::Event& e)
{
	m_cameraController.onEvent(e);
}

