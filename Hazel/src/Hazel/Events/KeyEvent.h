#pragma once

#include "Event.h"

#include <sstream>

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

	class HAZEL_API KeyPressedEvent
		: public KeyEvent
	{
	private:
		int m_repeatCount = 0;

	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), m_repeatCount(repeatCount)
		{

		}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		int getRepeatCount() const { return m_repeatCount; }

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class HAZEL_API KeyReleasedEvent
		: public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}
