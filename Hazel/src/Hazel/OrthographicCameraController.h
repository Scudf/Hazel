#pragma once

#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Core/Timestep.h"

namespace Hazel
{
	class OrthographicCameraController
	{
	private:
		float m_aspectRatio;
		float m_zoomLevel = 1.0f;
		OrthographicCamera m_camera;

		bool m_rotation;

		float m_cameraMoveSpeed = 5.0f;
		float m_cameraRotationSpeed = 180.0f;

		float m_cameraZoomSpeed = 0.25f;
		float m_minCameraZoom = 0.25f;
		float m_maxCameraZoom = 5.0f;

		void updateCameraProjection();

		bool onMouseScrolledEvent(MouseScrollEvent& e);
		bool onWindowResizedEvent(WindowResizeEvent& e);

	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void onUpdate(Timestep ts);
		void onEvent(Event& e);

		// Getters
		OrthographicCamera& getCamera() { return m_camera; }
		const OrthographicCamera& getCamera() const { return m_camera; }

		float getAspectRatio() const { return m_aspectRatio; }
		float getZoomLevel() const { return m_zoomLevel; }

		bool isRotationAllowed() const { return m_rotation; }

		float getCameraMoveSpeed() const { return m_cameraMoveSpeed; }
		float getCameraRotationSpeed() const { return m_cameraRotationSpeed; }

		float getCameraZoomSpeed() const { return m_cameraZoomSpeed; }
		float getMinCameraZoom() const { return m_minCameraZoom; }
		float getMaxCameraZoom() const { return m_maxCameraZoom; }

		// Setters
		void setAspectRatio(float aspectRatio) { m_aspectRatio = aspectRatio; }
		void setZoomLevel(float zoomLevel) { m_zoomLevel = zoomLevel; }

		void setRotationAllowed(bool rotation) { m_rotation = rotation; }

		void setCameraMoveSpeed(float cameraMoveSpeed) { m_cameraMoveSpeed; }
		void setCameraRotationSpeed(float cameraRotationSpeed) { m_cameraRotationSpeed = cameraRotationSpeed; }

		void setCameraZoomSpeed(float cameraZoomSpeed) { m_cameraZoomSpeed = cameraZoomSpeed; }
		void setMinCameraZoom(float minCameraZoom) { m_minCameraZoom = minCameraZoom; }
		void setMaxCameraZoom(float maxCameraZoom) { m_maxCameraZoom = maxCameraZoom; }
	};
}
