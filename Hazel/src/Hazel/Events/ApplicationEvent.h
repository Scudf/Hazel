#pragma once

#include "Event.h"

namespace Hazel
{
	class HAZEL_API WindowResizeEvent
		: public Event
	{
	private:
		uint32_t m_width{ 0 }, m_height{ 0 };

	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_width(width), m_height(height) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << ", " << m_height;
			return ss.str();
		}

		uint32_t getWidth() const { return m_width; }
		uint32_t getHeight() const { return m_height; }

		EVENT_CLASS_TYPE(WindowResized)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API WindowCloseEvent
		: public Event
	{
	public:
		EVENT_CLASS_TYPE(WindowClosed)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API AppTickEvent
		: public Event
	{
	public:
		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API AppUpdateEvent
		: public Event
	{
	public:
		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	
	class HAZEL_API AppRenderEvent
		: public Event
	{
	public:
		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
