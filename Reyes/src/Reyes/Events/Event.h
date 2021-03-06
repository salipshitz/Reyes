#pragma once

#include <pch>
#include <Reyes/Core/Core.h>

namespace Reyes
{
	enum class EEventType
	{
		NONE = 0,
		WIN_CLOSE,
		WIN_RESIZE,
		WIN_FOCUS,
		WIN_LOST_FOCUS,
		WIN_MOVED,
		APP_TICK,
		APP_UPDATE,
		APP_RENDER,
		KEY_DOWN,
		KEY_UP,
		KEY_REPEAT,
		KEY_TYPE,
		MOUSE_DOWN,
		MOUSE_UP,
		MOUSE_MOVE,
		MOUSE_SCROLL,
		MOUSE_DRAG
	};

	enum EEventCategory
	{
		NONE = 0U,
		APPLICATION = REY_BIT(0U),
		WINDOW = REY_BIT(1U),
		INPUT = REY_BIT(2U),
		KEYBOARD = REY_BIT(3U),
		MOUSE = REY_BIT(4U),
		MOUSE_MOTION = REY_BIT(5U),
		MOUSE_BUTTON = REY_BIT(6U),
	};

#define EVENT_CLASS_TYPE(type)                                     \
	static EEventType GetStaticType() { return EEventType::type; } \
	virtual EEventType GetType() const override { return GetStaticType(); }

#define EVENT_CLASS_CATEGORY(category) \
	virtual unsigned int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		bool Handled;

		[[nodiscard]] virtual EEventType GetType() const = 0;

		[[nodiscard]] virtual const char *GetName() const = 0;

		[[nodiscard]] virtual unsigned int GetCategoryFlags() const = 0;

		[[nodiscard]] virtual std::string ToString() const { return GetName(); }

		[[nodiscard]] inline bool IsInCategory(EEventCategory category) const { return GetCategoryFlags() & category; }
	};

	class EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T &)>;

	public:
		explicit EventDispatcher(Event &event) : m_Event(event) {}

		template <typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T *)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event &m_Event;
	};

	inline std::ostream &operator<<(std::ostream &os, const Event &e)
	{
		return os << e.ToString();
	}
} // namespace Reyes