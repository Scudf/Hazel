#include <Hazel.h>
#include <Hazel/Renderer/Renderer.h>
#include <Platform/OpenGL/OpenGLVertexArray.h>

class ExampleLayer
	: public Hazel::Layer
{
private:
	std::shared_ptr<Hazel::VertexArray> m_vertexArray;
	std::shared_ptr<Hazel::Shader> m_shader;

	std::shared_ptr<Hazel::VertexArray> m_redVertexArray;
	std::shared_ptr<Hazel::Shader> m_redShader;

public:
	void onAttach() override
	{
		m_vertexArray.reset(Hazel::OpenGLVertexArray::Create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.2f, 0.6f, 0.9f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.6f, 0.9f, 0.2f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.5f, 0.6f, 1.0f
		};

		Hazel::BufferLayout layouts = {
			{ Hazel::ShaderDataType::FLOAT3, "a_Position" },
			{ Hazel::ShaderDataType::FLOAT4, "a_Color" }
		};

		std::shared_ptr<Hazel::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hazel::OpenGLVertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->setLayout(layouts);
		m_vertexArray->addVertexBuffer(vertexBuffer);

		uint32_t indices[] = { 0, 1, 2 };
		std::shared_ptr<Hazel::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hazel::OpenGLIndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_vertexArray->setIndexBuffer(indexBuffer);

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
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

		m_shader.reset(new Hazel::Shader(vertexSource, fragmentSource));

		m_redVertexArray.reset(Hazel::OpenGLVertexArray::Create());

		float redVertices[] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		Hazel::BufferLayout redLayouts = {
			{ Hazel::ShaderDataType::FLOAT3, "a_Position" }
		};

		std::shared_ptr<Hazel::VertexBuffer> redVertexBuffer;
		redVertexBuffer.reset(Hazel::OpenGLVertexBuffer::Create(redVertices, sizeof(redVertices)));
		redVertexBuffer->setLayout(redLayouts);
		m_redVertexArray->addVertexBuffer(redVertexBuffer);

		uint32_t redIndices[] = { 0, 1, 2, 3, 2, 0 };
		std::shared_ptr<Hazel::IndexBuffer> redIndexBuffer;
		redIndexBuffer.reset(Hazel::OpenGLIndexBuffer::Create(redIndices, sizeof(redIndices) / sizeof(uint32_t)));
		m_redVertexArray->setIndexBuffer(redIndexBuffer);

		std::string redVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string redFragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			void main()
			{
				color = vec4(0.7, 0.1, 0.2, 1.0);
			}
		)";

		m_redShader.reset(new Hazel::Shader(redVertexSource, redFragmentSource));
	}


	void onDetach() override
	{
		
	}


	void onUpdate() override
	{
		
	}


	void onRender() override
	{
		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Hazel::RenderCommand::Clear();

		Hazel::Renderer::BeginScene();

		m_redShader->bind();
		Hazel::Renderer::Submit(m_redVertexArray);

		m_shader->bind();
		Hazel::Renderer::Submit(m_vertexArray);
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
