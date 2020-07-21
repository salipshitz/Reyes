#pragma once

#include "Event.h"
#include <glm/vec2.hpp>

namespace Reyes {
	class  WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_CATEGORY(WINDOW)
		EVENT_CLASS_TYPE(WIN_CLOSE)

		[[nodiscard]] inline const char *GetName() const override { return "WindowCloseEvent"; }
	};

	class  WindowResizeEvent : public Event {
	public:
		explicit WindowResizeEvent(const glm::vec2 size) : m_Size(size) {}

		inline const glm::vec2 &GetSize() { return m_Size; }

		[[nodiscard]] inline std::string ToString() const override {
			return std::string(GetName()) + ": Width = " + std::to_string(m_Size.x) + ", Height = " +
			       std::to_string(m_Size.y);
		}

		EVENT_CLASS_CATEGORY(WINDOW)
		EVENT_CLASS_TYPE(WIN_RESIZE)

		[[nodiscard]] inline const char *GetName() const override { return "WindowResizeEvent"; }

	private:
		glm::vec2 m_Size;
	};

	class  WindowFocusEvent : public Event {
	public:
		WindowFocusEvent() = default;

		EVENT_CLASS_CATEGORY(WINDOW)
		EVENT_CLASS_TYPE(WIN_FOCUS)

		[[nodiscard]] inline const char *GetName() const override { return "WindowFocusEvent"; }
	};

	class  WindowLostFocusEvent : public Event {
	public:
		WindowLostFocusEvent() = default;

		EVENT_CLASS_CATEGORY(WINDOW)
		EVENT_CLASS_TYPE(WIN_LOST_FOCUS)

		[[nodiscard]] inline const char *GetName() const override { return "WindowLostFocusEvent"; }

	};

	class  WindowMovedEvent : public Event {
	public:
		WindowMovedEvent(float x, float y) : m_X(x), m_Y(y) {}

		[[nodiscard]] inline float GetX() const { return m_X; }

		[[nodiscard]] inline float GetY() const { return m_Y; }

		[[nodiscard]] inline std::string ToString() const override {
			return std::string(GetName()) + ": X = " + std::to_string(m_X) + ", Y = " + std::to_string(m_Y);
		}

		EVENT_CLASS_CATEGORY(WINDOW)
		EVENT_CLASS_TYPE(WIN_MOVED)

		[[nodiscard]] inline const char *GetName() const override { return "WindowMovedEvent"; }

	private:
		float m_X, m_Y;
	};
}