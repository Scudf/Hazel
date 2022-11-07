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

	Hazel::Ref<Hazel::VertexArray> m_vertexArray;
	Hazel::Ref<Hazel::Shader> m_shader;

	Hazel::Ref<Hazel::VertexArray> m_redVertexArray;
	Hazel::Ref<Hazel::Shader> m_flatColorShader;

	Hazel::Ref<Hazel::Shader> m_textureShader;
	Hazel::Ref<Hazel::Texture2D> m_texture;

	float m_cameraMoveSpeed = 1.0f;
	float m_cameraRotationSpeed = 90.0f;

	glm::vec4 m_flatColor{ 1.0f };

public:
	ExampleLayer()
		: m_camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		// m_camera.setPosition({ 0.5f, 0.5f, 0.0f });
		// m_camera.setRotation(45.0f);
	}

	void onAttach() override
	{
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

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_shader = Hazel::Shader::Create(vertexSource, fragmentSource);

		m_redVertexArray.reset(Hazel::VertexArray::Create());

		float redVertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Hazel::BufferLayout redLayouts = {
			{ Hazel::ShaderDataType::FLOAT3, "a_Position" },
			{ Hazel::ShaderDataType::FLOAT2, "a_TexCoord" }
		};

		Hazel::Ref<Hazel::VertexBuffer> redVertexBuffer;
		redVertexBuffer = Hazel::OpenGLVertexBuffer::Create(redVertices, sizeof(redVertices));
		redVertexBuffer->setLayout(redLayouts);
		m_redVertexArray->addVertexBuffer(redVertexBuffer);

		uint32_t redIndices[] = { 0, 1, 2, 3, 2, 0 };
		Hazel::Ref<Hazel::IndexBuffer> redIndexBuffer;
		redIndexBuffer = Hazel::OpenGLIndexBuffer::Create(redIndices, sizeof(redIndices) / sizeof(uint32_t));
		m_redVertexArray->setIndexBuffer(redIndexBuffer);

		std::string cubeVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string cubeFragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform vec4 u_Color;

			void main()
			{
				color = u_Color;
			}
		)";

		m_flatColorShader = Hazel::Shader::Create(cubeVertexSource, cubeFragmentSource);

		std::string textureVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string textureFragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_textureShader = Hazel::Shader::Create(textureVertexSource, textureFragmentSource);

		m_texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");

		m_textureShader->bind();
		((Hazel::OpenGLShader*)(m_textureShader.get()))->uploadUniformInt("u_Texture", 0);
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

		m_flatColorShader->bind();
		((Hazel::OpenGLShader*)m_flatColorShader.get())->uploadUniformFloat4("u_Color", m_flatColor);

		for (int y = 0; y < 20; ++y)
		{
			for (int x = 0; x < 20; ++x)
			{
				glm::vec3 position = glm::vec3(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 trasform = glm::translate(glm::mat4(1.0f), position) * scale;
				Hazel::Renderer::Submit(m_flatColorShader, m_redVertexArray, trasform);
			}
		}

		// Triangle
		// Hazel::Renderer::Submit(m_shader, m_vertexArray);
		
		m_texture->bind();
		Hazel::Renderer::Submit(m_textureShader, m_redVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

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
