#pragma once

#include <Hazel.h>

class Sandbox2D
	: public Hazel::Layer
{
private:
	Hazel::OrthographicCameraController m_cameraController;

	Hazel::Ref<Hazel::Shader> m_flatColorShader;
	Hazel::Ref<Hazel::VertexArray> m_squareVertexArray;
	glm::vec4 m_flatColor{ 1.0f };

public:
	Sandbox2D();
	~Sandbox2D() override = default;

	void onAttach() override;
	void onDetach() override;

	void onUpdate(Hazel::Timestep ts) override;
	void onImGUIRender() override;
	void onEvent(Hazel::Event& e) override;
};
