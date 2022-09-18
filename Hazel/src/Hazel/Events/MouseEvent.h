#pragma once

#include "Event.h"

#include <sstream>

namespace Hazel
{
	class HAZEL_API MouseMovedEvent
		: public Event
	{
	protected:
		float m_x{ 0 }, m_y{ 0 };

	public:
		MouseMovedEvent(float x, float y) { }

		float getX() const { return m_x; }
		float getY() const { return m_y; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_x << ", " << m_y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class HAZEL_API MouseScrolledEvent
		: public Event
	{
	protected:
		float m_xOffset{ 0 }, m_yOffset{ 0 };

	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_xOffset(xOffset), m_yOffset(yOffset) { }

		float getXOffset() const { return m_xOffset; }
		float getYOffset() const { return m_yOffset; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_xOffset << ", " << m_yOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class HAZEL_API MouseButtonEvent
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

	class HAZEL_API MouseButtonPressedEvent
		: public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MousePressedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class HAZEL_API MouseButtonReleasedEvent
		: public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
};
