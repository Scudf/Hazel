#pragma once

#include <glm/glm.hpp>

namespace Hazel
{
	class OrthographicCamera
	{
	private:
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_viewProjectionMatrix;

		glm::vec3 m_position{ 0.0f };
		float m_rotation = 0;

		void recalculateViewMatrix();

	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }
		const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
		const glm::mat4& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }

		const glm::vec3& getPosition() const { return m_position; }
		void setPosition(const glm::vec3& position) { m_position = position; recalculateViewMatrix(); }

		float getRotation() const { return m_rotation; }
		void setRotation(float rotation) { m_rotation = rotation; recalculateViewMatrix(); }

		void move(float x, float y) { m_position.x += x, m_position.y += y; recalculateViewMatrix(); }
		void rotate(float degrees) { m_rotation += degrees; recalculateViewMatrix(); }
	};
}
