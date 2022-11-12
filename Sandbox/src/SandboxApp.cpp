#include <Hazel.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include "imgui/imgui.h"

#include <glm/glm/ext/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

class ExampleLayer
	: public Hazel::Layer
{
private:
	Hazel::OrthographicCamera m_camera;

	Hazel::ShaderLibrary m_shaderLibrary;

	Hazel::Ref<Hazel::Texture2D> m_checkerboardTexture, m_alphaTexture;

	Hazel::Ref<Hazel::VertexArray> m_vertexArray, m_squareVertexArray;

	float m_cameraMoveSpeed = 1.0f;
	float m_cameraRotationSpeed = 90.0f;

	glm::vec4 m_flatColor{ 1.0f };

public:
	ExampleLayer()
		: m_camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		// Init assets
		m_shaderLibrary.load("assets/shaders/Basic.glsl");
		m_shaderLibrary.load("assets/shaders/FlatColor.glsl");
		m_shaderLibrary.load("assets/shaders/Texture.glsl");

		m_checkerboardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
		m_alphaTexture = Hazel::Texture2D::Create("assets/textures/ChernoLogo.png");

		// Init models
		// Triangle
		m_vertexArray.reset(Hazel::VertexArray::Create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.2f, 0.6f, 0.9f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.6f, 0.9f, 0.2f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.5f, 0.6f, 1.0f
		};

		Hazel::BufferLayout layouts = {
			{ Hazel::ShaderDataType::FLOAT3, "a_Position" },
			{ Hazel::ShaderDataType::FLOAT4, "a_Color" }
		};

		Hazel::Ref<Hazel::VertexBuffer> vertexBuffer;
		vertexBuffer = Hazel::OpenGLVertexBuffer::Create(vertices, sizeof(vertices));
		vertexBuffer->setLayout(layouts);
		m_vertexArray->addVertexBuffer(vertexBuffer);

		uint32_t indices[] = { 0, 1, 2 };
		Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
		indexBuffer = Hazel::OpenGLIndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_vertexArray->setIndexBuffer(indexBuffer);

		// Square
		m_squareVertexArray.reset(Hazel::VertexArray::Create());

		float squareVertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Hazel::BufferLayout squareLayouts = {
			{ Hazel::ShaderDataType::FLOAT3, "a_Position" },
			{ Hazel::ShaderDataType::FLOAT2, "a_TexCoord" }
		};

		Hazel::Ref<Hazel::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer = Hazel::OpenGLVertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVertexBuffer->setLayout(squareLayouts);
		m_squareVertexArray->addVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[] = { 0, 1, 2, 3, 2, 0 };
		Hazel::Ref<Hazel::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer = Hazel::OpenGLIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_squareVertexArray->setIndexBuffer(squareIndexBuffer);

		auto textureShader = m_shaderLibrary.get("Texture");
		textureShader->bind();
		((Hazel::OpenGLShader*)(textureShader.get()))->uploadUniformInt("u_Texture", 0);
	}

	void onAttach() override
	{
		
	}

	void onDetach() override
	{
		
	}

	void onUpdate(Hazel::Timestep ts) override
	{
		const float movement = m_cameraMoveSpeed * ts;
		const float rotation = m_cameraRotationSpeed * ts;

		// Y movement
		if (Hazel::Input::IsKeyPressed(HZ_KEY_W))
			m_camera.move(0, movement);
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_S))
			m_camera.move(0, -movement);

		// X movement
		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
			m_camera.move(-movement, 0);
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
			m_camera.move(movement, 0);

		// Rotation
		if (Hazel::Input::IsKeyPressed(HZ_KEY_Q))
			m_camera.rotate(rotation);
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_E))
			m_camera.rotate(-rotation);

		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Hazel::RenderCommand::Clear();

		Hazel::Renderer::BeginScene(m_camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		auto flatColorShader = m_shaderLibrary.get("FlatColor");
		flatColorShader->bind();
		((Hazel::OpenGLShader*)flatColorShader.get())->uploadUniformFloat4("u_Color", m_flatColor);

		for (int y = 0; y < 20; ++y)
		{
			for (int x = 0; x < 20; ++x)
			{
				glm::vec3 position = glm::vec3(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 trasform = glm::translate(glm::mat4(1.0f), position) * scale;
				Hazel::Renderer::Submit(flatColorShader, m_squareVertexArray, trasform);
			}
		}

		// Triangle
		// Hazel::Renderer::Submit(m_shader, m_vertexArray);
		
		auto textureShader = m_shaderLibrary.get("Texture");

		m_checkerboardTexture->bind();
		Hazel::Renderer::Submit(textureShader, m_squareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_alphaTexture->bind();
		Hazel::Renderer::Submit(textureShader, m_squareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Hazel::Renderer::EndScene();
	}

	void onRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Color", glm::value_ptr(m_flatColor));
		ImGui::End();
	}


	void onEvent(Hazel::Event& e) override
	{

	}
};

class Sandbox
	: public Hazel::Application
{
public:
	Sandbox()
	{
		pushOverlay(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}
