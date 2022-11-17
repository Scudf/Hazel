#include "hzpch.h"
#include "OrthographicCameraController.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"

namespace Hazel
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation /*= false*/)
		: m_camera(-aspectRatio * m_zoomLevel, aspectRatio* m_zoomLevel, -m_zoomLevel, m_zoomLevel)
		, m_aspectRatio(aspectRatio)
		, m_rotation(rotation)
	{

	}

	void OrthographicCameraController::updateCameraProjection()
	{
		m_camera.setProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
	}

	void OrthographicCameraController::onUpdate(Timestep ts)
	{
		HZ_PROFILE_FUNCTION();

		const float cameraRotation = m_camera.getRotation();
		const float movement = m_cameraMoveSpeed * ts;
		const float rotation = m_cameraRotationSpeed * ts;
		const float l_sin = sin(glm::radians(m_camera.getRotation())) * movement;
		const float l_cos = cos(glm::radians(m_camera.getRotation())) * movement;

		// Y movement
		if (Hazel::Input::IsKeyPressed(HZ_KEY_W))
			m_camera.move(-l_sin, l_cos);
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_S))
			m_camera.move(l_sin, -l_cos);

		// X movement
		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
			m_camera.move(-l_cos, -l_sin);
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
			m_camera.move(l_cos, l_sin);

		// Rotation
		if (m_rotation)
		{
			if (Hazel::Input::IsKeyPressed(HZ_KEY_Q))
				m_camera.rotate(rotation);
			else if (Hazel::Input::IsKeyPressed(HZ_KEY_E))
				m_camera.rotate(-rotation);

			if (cameraRotation > 180.0f)
				m_camera.rotate(-360.0f);
			else if (cameraRotation <= -180.0f)
				m_camera.rotate(360.0);
		}
	}

	void OrthographicCameraController::onEvent(Event& e)
	{
		HZ_PROFILE_FUNCTION();

		EventDispatcher eventDispatcher(e);
		eventDispatcher.dispatch<MouseScrollEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolledEvent));
		eventDispatcher.dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::onWindowResizedEvent));
	}

	bool OrthographicCameraController::onMouseScrolledEvent(MouseScrollEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		m_zoomLevel -= e.getYOffset() * m_cameraZoomSpeed;
		m_zoomLevel = std::max(m_zoomLevel, m_minCameraZoom);
		m_zoomLevel = std::min(m_zoomLevel, m_maxCameraZoom);
		updateCameraProjection();

		return false;
	}

	bool OrthographicCameraController::onWindowResizedEvent(WindowResizeEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		m_aspectRatio = (float)e.getWidth() / (float)e.getHeight();
		updateCameraProjection();

		return false;
	}
}
