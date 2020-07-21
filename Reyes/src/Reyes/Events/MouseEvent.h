#pragma once

#include "Event.h"

namespace Reyes {
	class  MouseButtonEvent : public Event {
	public:
		[[nodiscard]] inline std::string ToString() const override {
			return std::string(GetName()) + ": Mouse Button = " + std::to_string(GetMouseButton());
		}

		[[nodiscard]] inline int GetMouseButton() const { return m_MouseButton; }

		EVENT_CLASS_CATEGORY(MOUSE_BUTTON | MOUSE | INPUT)

	protected:
		int m_MouseButton;

		explicit MouseButtonEvent(int mouseButton) : m_MouseButton(mouseButton) {}
	};

	class  MouseDownEvent : public MouseButtonEvent {
	public:
		explicit MouseDownEvent(int mouseButton) : MouseButtonEvent(mouseButton) {}

		EVENT_CLASS_TYPE(MOUSE_DOWN)

		[[nodiscard]] inline const char *GetName() const override { return "MouseDownEvent"; }
	};

	class  MouseUpEvent : public MouseButtonEvent {
	public:
		explicit MouseUpEvent(int mouseButton) : MouseButtonEvent(mouseButton) {}

		EVENT_CLASS_TYPE(MOUSE_UP)

		[[nodiscard]] inline const char *GetName() const override { return "MouseUpEvent"; }

	};

	class  MouseMotionEvent : public Event {
	public:
		[[nodiscard]] inline float GetX() const { return m_MouseX; }

		[[nodiscard]] inline float GetY() const { return m_MouseY; }

		[[nodiscard]] inline std::string ToString() const override {
			return std::string(GetName()) + ": Mouse X = " + std::to_string(GetX()) + ", Mouse Y = " +
			       std::to_string(GetY());
		}

		EVENT_CLASS_CATEGORY(MOUSE_MOTION | MOUSE | INPUT)
	protected:
		float m_MouseX, m_MouseY;

		MouseMotionEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}
	};

	class  MouseMoveEvent : public MouseMotionEvent {
	public:
		MouseMoveEvent(float x, float y) : MouseMotionEvent(x, y) {}

		EVENT_CLASS_TYPE(MOUSE_MOVE)

		inline const char *GetName() const override { return "MouseMoveEvent"; }
	};

	class  MouseDragEvent : MouseMotionEvent {
	public:
		MouseDragEvent(float x, float y) : MouseMotionEvent(x, y) {}

		EVENT_CLASS_TYPE(MOUSE_DRAG)

		[[nodiscard]] inline const char *GetName() const override { return "MouseDragEvent"; }
	};

	class  MouseScrollEvent : public Event {
	public:
		MouseScrollEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

		[[nodiscard]] inline float GetXOffset() const { return m_XOffset; }

		[[nodiscard]] inline float GetYOffset() const { return m_YOffset; }

		[[nodiscard]] inline std::string ToString() const override {
			return std::string(GetName()) + ": X Offset = " + std::to_string(GetXOffset()) + ", Y Offset = " +
			       std::to_string(GetYOffset());
		}

		EVENT_CLASS_CATEGORY(MOUSE_MOTION | MOUSE | INPUT)

		EVENT_CLASS_TYPE(MOUSE_SCROLL)

		[[nodiscard]] inline const char *GetName() const override { return "MouseScrollEvent"; }
	private:
		float m_XOffset, m_YOffset;
	};
}