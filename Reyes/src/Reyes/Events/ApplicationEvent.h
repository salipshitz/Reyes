#pragma once

#include "Event.h"

namespace Reyes {
	class  ApplicationTickEvent : public Event {
	public:
		explicit ApplicationTickEvent(float deltaSeconds) : m_DeltaSeconds(deltaSeconds) {}

		EVENT_CLASS_CATEGORY(APPLICATION)
		EVENT_CLASS_TYPE(APP_TICK)

		[[nodiscard]] inline const char *GetName() const override { return "ApplicationTickEvent"; }

	private:
		float m_DeltaSeconds;
	};

	class  ApplicationUpdateEvent : public Event {
	public:
		ApplicationUpdateEvent() = default;

		EVENT_CLASS_CATEGORY(APPLICATION)
		EVENT_CLASS_TYPE(APP_UPDATE)

		[[nodiscard]] inline const char *GetName() const override { return "ApplicationUpdateEvent"; }

	};

	class  ApplicationRenderEvent : public Event {
	public:
		ApplicationRenderEvent() = default;

		EVENT_CLASS_CATEGORY(APPLICATION)
		EVENT_CLASS_TYPE(APP_RENDER)

		[[nodiscard]] inline const char *GetName() const override { return "ApplicationRenderEvent"; }
	};
}