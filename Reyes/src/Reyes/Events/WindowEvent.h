#pragma once

#include "Event.h"

namespace Reyes {
	class REYES_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_CATEGORY(WINDOW)

		EVENT_CLASS_TYPE(WIN_CLOSE)

		[[nodiscard]] inline const char *GetName() const override { return "WindowCloseEvent"; }
	};

	class REYES_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

		[[nodiscard]] inline unsigned int GetWidth() const { return m_Width; }

		[[nodiscard]] inline unsigned int GetHeight() const { return m_Height; }

		[[nodiscard]] inline std::string ToString() const override {
			return std::string(GetName()) + ": Width = " + std::to_string(m_Width) + ", Height = " +
			       std::to_string(m_Height);
		}

		EVENT_CLASS_CATEGORY(WINDOW)

		EVENT_CLASS_TYPE(WIN_RESIZE)

		[[nodiscard]] inline const char *GetName() const override { return "WindowResizeEvent"; }

	private:
		unsigned int m_Width, m_Height;
	};

	class REYES_API WindowFocusEvent : public Event {
	public:
		WindowFocusEvent() = default;

		EVENT_CLASS_CATEGORY(WINDOW)

		EVENT_CLASS_TYPE(WIN_FOCUS)

		[[nodiscard]] inline const char *GetName() const override { return "WindowFocusEvent"; }
	};

	class REYES_API WindowLostFocusEvent : public Event {
	public:
		WindowLostFocusEvent() = default;

		EVENT_CLASS_CATEGORY(WINDOW)

		EVENT_CLASS_TYPE(WIN_LOST_FOCUS)

		[[nodiscard]] inline const char *GetName() const override { return "WindowLostFocusEvent"; }

	};

	class REYES_API WindowMovedEvent : public Event {
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