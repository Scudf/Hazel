#include "Sandbox2D.h"

#include <Platform/OpenGL/OpenGLShader.h>
#include <imgui/imgui.h>
#include <glm/glm/ext/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: m_cameraController(2560.0f / 1440.0f)
{
	m_flatColorShader = Hazel::Shader::Create("assets/shaders/FlatColor.glsl");

	m_squareVertexArray = Hazel::VertexArray::Create();

	float squareVertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Hazel::BufferLayout squareLayouts = {
		{ Hazel::ShaderDataType::FLOAT3, "a_Position" }
	};

	Hazel::Ref<Hazel::VertexBuffer> squareVertexBuffer;
	squareVertexBuffer = Hazel::OpenGLVertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVertexBuffer->setLayout(squareLayouts);
	m_squareVertexArray->addVertexBuffer(squareVertexBuffer);

	uint32_t squareIndices[] = { 0, 1, 2, 3, 2, 0 };
	Hazel::Ref<Hazel::IndexBuffer> squareIndexBuffer;
	squareIndexBuffer = Hazel::OpenGLIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_squareVertexArray->setIndexBuffer(squareIndexBuffer);
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

	Hazel::Renderer::BeginScene(m_cameraController.getCamera());

	m_flatColorShader->bind();
	((Hazel::OpenGLShader*)m_flatColorShader.get())->uploadUniformFloat4("u_Color", m_flatColor);
	Hazel::Renderer::Submit(m_flatColorShader, m_squareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Hazel::Renderer::EndScene();
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

