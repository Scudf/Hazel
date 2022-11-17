#pragma once

#include "hzpch.h"
#include "Hazel/Core/Core.h"

namespace Hazel
{
	enum class EEventType
	{
		None,
		WindowClosed, WindowResized, WindowFocused, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EEventCategory
	{
		None,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type)			static EEventType GetStaticType() { return EEventType::type; }\
										EEventType getEventType() const override { return GetStaticType(); }\
										const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)	int getEventCategoryFlag() const override { return category; }

	class Event
	{
	public:
		bool isHandled = false;

		virtual EEventType getEventType() const = 0;
		virtual int getEventCategoryFlag() const = 0;
		virtual const char* getName() const = 0;
		virtual std::string toString() const { return getName(); }

		bool isInCategory(EEventCategory category) { return category & getEventCategoryFlag(); }
	};

	class EventDispatcher
	{
	private:
		Event& m_event;

	public:
		EventDispatcher(Event& _event)
			: m_event(_event)
		{

		}

		template<typename T, typename F>
		bool dispatch(const F& func)
		{
			if (m_event.getEventType() == T::GetStaticType())
			{
				m_event.isHandled = func(static_cast<T&>(m_event));
				return true;
			}
			return false;
		}
	};

	inline std::ostream& operator<<(std::ostream& out, const Event& e)
	{
		return out << e.toString();
	}
}
