#include "hzpch.h"

#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Hazel/Renderer/Renderer.h"

namespace Hazel
{
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->setEventCallback(HZ_BIND_EVENT_FN(Application::onEvent));

		m_imGuiLayer = new ImGuiLayer();
		pushOverlay(m_imGuiLayer);

		m_vertexArray.reset(OpenGLVertexArray::Create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.2f, 0.6f, 0.9f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.6f, 0.9f, 0.2f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.5f, 0.6f, 1.0f
		};

		BufferLayout layouts = {
			{ ShaderDataType::FLOAT3, "a_Position" },
			{ ShaderDataType::FLOAT4, "a_Color" }
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(OpenGLVertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->setLayout(layouts);
		m_vertexArray->addVertexBuffer(vertexBuffer);

		uint32_t indices[] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(OpenGLIndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
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

		m_shader.reset(new Shader(vertexSource, fragmentSource));

		m_redVertexArray.reset(OpenGLVertexArray::Create());

		float redVertices[] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		BufferLayout redLayouts = {
			{ ShaderDataType::FLOAT3, "a_Position" }
		};

		std::shared_ptr<VertexBuffer> redVertexBuffer;
		redVertexBuffer.reset(OpenGLVertexBuffer::Create(redVertices, sizeof(redVertices)));
		redVertexBuffer->setLayout(redLayouts);
		m_redVertexArray->addVertexBuffer(redVertexBuffer);

		uint32_t redIndices[] = { 0, 1, 2, 3, 2, 0 };
		std::shared_ptr<IndexBuffer> redIndexBuffer;
		redIndexBuffer.reset(OpenGLIndexBuffer::Create(redIndices, sizeof(redIndices) / sizeof(uint32_t)));
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

		m_redShader.reset(new Shader(redVertexSource, redFragmentSource));
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (m_running)
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_redShader->bind();
			Renderer::Submit(m_redVertexArray);

			m_shader->bind();
			Renderer::Submit(m_vertexArray);

			for (Layer* layer : m_layerStack)
				layer->onUpdate();

			m_imGuiLayer->begin();
			for (Layer* layer : m_layerStack)
				layer->onRender();
			m_imGuiLayer->end();

			m_window->onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher eventDispatcher(e);
		eventDispatcher.dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::onWindowClose));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->onEvent(e);
			if (e.isHandled)
				break;
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* overlay)
	{
		m_layerStack.pushOverlay(overlay);
		overlay->onAttach();
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}
}
