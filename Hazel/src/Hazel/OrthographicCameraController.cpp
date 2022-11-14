#include "hzpch.h"
#include "OrthographicCameraController.h"

#include "Hazel/Input.h"
#include "Hazel/KeyCodes.h"

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
		if (m_rotation)
		{
			if (Hazel::Input::IsKeyPressed(HZ_KEY_Q))
				m_camera.rotate(rotation);
			else if (Hazel::Input::IsKeyPressed(HZ_KEY_E))
				m_camera.rotate(-rotation);
		}
	}

	void OrthographicCameraController::onEvent(Event& e)
	{
		EventDispatcher eventDispatcher(e);
		eventDispatcher.dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolledEvent));
		eventDispatcher.dispatch<WindowResizedEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::onWindowResizedEvent));
	}

	bool OrthographicCameraController::onMouseScrolledEvent(MouseScrolledEvent& e)
	{
		m_zoomLevel -= e.getYOffset() * m_cameraZoomSpeed;
		m_zoomLevel = std::max(m_zoomLevel, m_minCameraZoom);
		m_zoomLevel = std::min(m_zoomLevel, m_maxCameraZoom);
		updateCameraProjection();

		return false;
	}

	bool OrthographicCameraController::onWindowResizedEvent(WindowResizedEvent& e)
	{
		m_aspectRatio = (float)e.getWidth() / (float)e.getHeight();
		updateCameraProjection();

		return false;
	}
}
