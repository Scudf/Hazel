#pragma once

#include "Event.h"

namespace Hazel
{
	class HAZEL_API KeyEvent
		: public Event
	{
	protected:
		int m_keyCode = 0;

		KeyEvent(int keyCode)
			: m_keyCode(keyCode)
		{

		}

	public:
		int getKeyCode() const { return m_keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	};

	class HAZEL_API KeyPressEvent
		: public KeyEvent
	{
	private:
		int m_repeatCount = 0;

	public:
		KeyPressEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), m_repeatCount(repeatCount)
		{

		}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		int getRepeatCount() const { return m_repeatCount; }

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class HAZEL_API KeyReleaseEvent
		: public KeyEvent
	{
	public:
		KeyReleaseEvent(int keyCode)
			: KeyEvent(keyCode) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyReleaseEvent: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class HAZEL_API KeyTypeEvent
		: public KeyEvent
	{
	public:
		KeyTypeEvent(int keyCode)
			: KeyEvent(keyCode) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyTypeEvent: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}
