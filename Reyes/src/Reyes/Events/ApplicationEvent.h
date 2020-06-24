#pragma once

#include "Event.h"

namespace Reyes {
	class REYES_API ApplicationTickEvent : public Event {
	public:
		explicit ApplicationTickEvent(float deltaSeconds) : m_DeltaSeconds(deltaSeconds) {}

		EVENT_CLASS_CATEGORY(APPLICATION)

		EVENT_CLASS_TYPE(APP_TICK)

		inline const char *GetName() const override { return "ApplicationTickEvent"; }

	private:
		float m_DeltaSeconds;
	};

	class REYES_API ApplicationUpdateEvent : public Event {
	public:
		ApplicationUpdateEvent() = default;

		EVENT_CLASS_CATEGORY(APPLICATION)

		EVENT_CLASS_TYPE(APP_UPDATE)

		inline const char *GetName() const override { return "ApplicationUpdateEvent"; }

	};

	class REYES_API ApplicationRenderEvent : public Event {
	public:
		ApplicationRenderEvent() = default;

		EVENT_CLASS_CATEGORY(APPLICATION)

		EVENT_CLASS_TYPE(APP_RENDER)

		inline const char *GetName() const override { return "ApplicationRenderEvent"; }
	};
}