#pragma once

#include <Hazel.h>

class Sandbox2D
	: public Hazel::Layer
{
private:
	Hazel::OrthographicCameraController m_cameraController;

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
