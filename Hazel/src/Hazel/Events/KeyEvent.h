#pragma once

#include "Hazel/Events/Event.h"
#include "Hazel/Core/KeyCodes.h"

namespace Hazel
{
	class KeyEvent
		: public Event
	{
	protected:
		KeyCode m_keyCode;

		KeyEvent(KeyCode keyCode)
			: m_keyCode(keyCode) { }

	public:
		KeyCode getKeyCode() const { return m_keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	};

	class KeyPressEvent
		: public KeyEvent
	{
	private:
		int m_repeatCount = 0;

	public:
		KeyPressEvent(KeyCode keyCode, int repeatCount)
			: KeyEvent(keyCode), m_repeatCount(repeatCount) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		int getRepeatCount() const { return m_repeatCount; }

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class KeyReleaseEvent
		: public KeyEvent
	{
	public:
		KeyReleaseEvent(KeyCode keyCode)
			: KeyEvent(keyCode) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyReleaseEvent: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypeEvent
		: public KeyEvent
	{
	public:
		KeyTypeEvent(KeyCode keyCode)
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
