#pragma once

#include "Hazel/Events/Event.h"

namespace Hazel
{
	class MouseMoveEvent
		: public Event
	{
	protected:
		float m_x{ 0 }, m_y{ 0 };

	public:
		MouseMoveEvent(float x, float y)
			: m_x(x), m_y(y) { }

		float getX() const { return m_x; }
		float getY() const { return m_y; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMoveEvent: " << m_x << ", " << m_y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class MouseScrollEvent
		: public Event
	{
	protected:
		float m_xOffset{ 0 }, m_yOffset{ 0 };

	public:
		MouseScrollEvent(float xOffset, float yOffset)
			: m_xOffset(xOffset), m_yOffset(yOffset) { }

		float getXOffset() const { return m_xOffset; }
		float getYOffset() const { return m_yOffset; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScrollEvent: " << m_xOffset << ", " << m_yOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class MouseButtonEvent
		: public Event
	{
	protected:
		int m_button = 0;

		MouseButtonEvent(int button)
			: m_button(button) { }

	public:
		int getMouseButton() const { return m_button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class MouseButtonPressEvent
		: public MouseButtonEvent
	{
	public:
		MouseButtonPressEvent(int button)
			: MouseButtonEvent(button) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleaseEvent
		: public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(int button)
			: MouseButtonEvent(button) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleaseEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
};
