#include "hzpch.h"

#include "Application.h"

#include <glad/glad.h>

#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"

namespace Hazel
{
	static uint32_t ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Hazel::ShaderDataType::FLOAT:		return GL_FLOAT;
			case Hazel::ShaderDataType::FLOAT2:		return GL_FLOAT;
			case Hazel::ShaderDataType::FLOAT3:		return GL_FLOAT;
			case Hazel::ShaderDataType::FLOAT4:		return GL_FLOAT;
			case Hazel::ShaderDataType::INT:		return GL_INT;
			case Hazel::ShaderDataType::INT2:		return GL_INT;
			case Hazel::ShaderDataType::INT3:		return GL_INT;
			case Hazel::ShaderDataType::INT4:		return GL_INT;
			case Hazel::ShaderDataType::MAT3:		return GL_FLOAT;
			case Hazel::ShaderDataType::MAT4:		return GL_FLOAT;
			case Hazel::ShaderDataType::BOOL:		return GL_BOOL;
		}

		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->setEventCallback(HZ_BIND_EVENT_FN(Application::onEvent));

		m_imGuiLayer = new ImGuiLayer();
		pushOverlay(m_imGuiLayer);
		
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.2f, 0.6f, 0.9f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.6f, 0.9f, 0.2f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.9f, 0.2f, 0.6f, 1.0f
		};

		glGenVertexArrays(1, &m_vertexArray);
		glBindVertexArray(m_vertexArray);

		m_vertexBuffer.reset(OpenGLVertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layouts = {
				{ ShaderDataType::FLOAT3, "a_Position" },
				{ ShaderDataType::FLOAT4, "a_Color" }
			};

			m_vertexBuffer->setLayout(layouts);
		}

		const auto& layouts = m_vertexBuffer->getLayout();
		uint32_t index = 0;
		for (auto& layout : layouts)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index++,
				layout.getComponentCount(),
				ShaderDataTypeToOpenGLBaseType(layout.type),
				layout.normalized,
				layouts.getStride(),
				(const void*)layout.offset);
		}

		uint32_t indices[] = { 0, 1, 2 };
		m_indexBuffer.reset(OpenGLIndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		glBindVertexArray(0);

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
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (m_running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_shader->bind();
			glBindVertexArray(m_vertexArray);
			glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);

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
