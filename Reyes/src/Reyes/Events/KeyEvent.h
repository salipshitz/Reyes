#pragma once

#include "Event.h"

namespace Reyes {
	class  KeyEvent : public Event {
	public:
		[[nodiscard]] inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EEventCategory::INPUT | EEventCategory::KEYBOARD)

		[[nodiscard]] inline std::string ToString() const override {
			return std::string(GetName()) + ": Key Code = " + std::to_string(GetKeyCode());
		}

	protected:
		explicit KeyEvent(int keycode) : m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class  KeyDownEvent : public KeyEvent {
	public:
		explicit KeyDownEvent(int keycode) : KeyEvent(keycode) {}

		EVENT_CLASS_TYPE(KEY_DOWN)

		[[nodiscard]] inline const char *GetName() const override { return "KeyDownEvent"; }
	};

	class  KeyRepeatEvent : public KeyEvent {
	public:
		KeyRepeatEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		EVENT_CLASS_TYPE(KEY_REPEAT)

		[[nodiscard]] inline std::string ToString() const override {
			return KeyEvent::ToString() + ", repetitions: " + std::to_string(m_RepeatCount);
		}

		[[nodiscard]] inline const char *GetName() const override { return "KeyRepeatEvent"; }

	protected:
		int m_RepeatCount;
	};

	class  KeyUpEvent : public KeyEvent {
	public:
		explicit KeyUpEvent(int keycode) : KeyEvent(keycode) {}

		EVENT_CLASS_TYPE(KEY_UP)

		[[nodiscard]] inline const char *GetName() const override { return "KeyUpEvent"; }

	};

	class  KeyTypeEvent : public KeyEvent {
	public:
		explicit KeyTypeEvent(int keycode) : KeyEvent(keycode) {}

		EVENT_CLASS_TYPE(KEY_TYPE)

		[[nodiscard]] inline const char *GetName() const override { return "KeyTypeEvent"; }
	};
}