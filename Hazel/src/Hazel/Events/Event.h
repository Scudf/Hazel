#pragma once

#include "hzpch.h"
#include "Hazel/Core.h"

namespace Hazel
{
	enum class EEventType
	{
		None,
		WindowClose, WindowResize, WindowFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
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

#define EVENT_CLASS_TYPE(type)			static EEventType GetStaticType() { return EEventType::##type; }\
										EEventType getEventType() const override { return GetStaticType(); }\
										const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)	int getEventCategoryFlag() const override { return category; }

	class HAZEL_API Event
	{
		friend class EventDispatcher;

	public:
		virtual EEventType getEventType() const = 0;
		virtual int getEventCategoryFlag() const = 0;
		virtual const char* getName() const = 0;
		virtual std::string toString() const { return getName(); }

		bool isInCategory(EEventCategory category) { return category & getEventCategoryFlag(); }

	protected:
		bool m_isHandled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	private:
		Event& m_event;

	public:
		EventDispatcher(Event& _event)
			: m_event(_event)
		{

		}

		template<typename T>
		bool dispatch(EventFn<T> _event)
		{
			if (m_event.getEventType() == T::GetStaticType())
			{
				m_event.m_isHandled = func(*(T*)&m_event);
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
