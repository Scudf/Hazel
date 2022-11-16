#include "hzpch.h"
#include "Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel
{
	struct Renderer2DStorage
	{
		Renderer2DStorage() = default;

		Hazel::Ref<Hazel::Shader> FlatColorShader;
		Hazel::Ref<Hazel::Shader> TextureShader;
		Hazel::Ref<Hazel::VertexArray> SquareVertexArray;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->FlatColorShader = Hazel::Shader::Create("assets/shaders/FlatColor.glsl");
		s_Data->TextureShader = Hazel::Shader::Create("assets/shaders/Texture.glsl");
		s_Data->SquareVertexArray = Hazel::VertexArray::Create();

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
		s_Data->SquareVertexArray->addVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[] = { 0, 1, 2, 3, 2, 0 };
		Hazel::Ref<Hazel::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer = Hazel::OpenGLIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->SquareVertexArray->setIndexBuffer(squareIndexBuffer);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->TextureShader->bind();
		s_Data->TextureShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
		s_Data->FlatColorShader->bind();
		s_Data->FlatColorShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(
		const glm::vec2& position,
		float rotation,
		const glm::vec2& scale,
		const glm::vec4& color,
		const Ref<Texture2D>& texture,
		float wrap)
	{
		DrawQuad(glm::vec3(position, 1.0f), glm::vec3(0.0f, 0.0f, rotation), glm::vec3(scale, 1.0f), color, texture, glm::vec2(wrap));
	}

	void Renderer2D::DrawQuad(
		const glm::vec3& position,
		const glm::vec3& rotation,
		const glm::vec3& scale,
		const glm::vec4& color,
		const Ref<Texture2D>& texture,
		const glm::vec2& wrap)
	{
		auto shader = texture ? s_Data->TextureShader : s_Data->FlatColorShader;
		if (texture)
		{
			texture->bind();
			s_Data->TextureShader->bind();
			s_Data->TextureShader->setInt("u_Texture", 0);
			s_Data->TextureShader->setFloat2("u_Wrap", wrap);
		}
		else
		{
			s_Data->FlatColorShader->bind();
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), scale);
		
		shader->setFloat4("u_Color", color);
		shader->setMat4("u_Transform", transform);

		s_Data->SquareVertexArray->bind();
		RenderCommand::DrawIndexed(s_Data->SquareVertexArray);

		if (texture)
			texture->unbind();
	}
}
