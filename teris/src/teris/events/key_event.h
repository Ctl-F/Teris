#pragma once

#include "event.h"

namespace teris {
	class TERIS_API KeyEvent : public Event {
	public:
		inline int get_key_code() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode) : m_KeyCode{ keycode } {};

		int m_KeyCode;
	};

	class TERIS_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int repeateCount) : KeyEvent(keycode), m_RepeatCount(repeateCount) {}

		inline int get_repeat_count() const { return m_RepeatCount; }

		std::string to_string() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	protected:
		int m_RepeatCount;
	};

	class TERIS_API KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {}


		std::string to_string() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

	class TERIS_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {};

		std::string to_string() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}