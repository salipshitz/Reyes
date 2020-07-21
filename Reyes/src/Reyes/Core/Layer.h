#pragma once
#include <pch>

#include "Core.h"

namespace Reyes {
	class Event;
	
	class  Layer {
	public:
		explicit Layer(const char *name = "Layer") : m_DebugName(name) {}
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float deltaSeconds) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event &event) {}

		[[nodiscard]] inline std::string GetName() const { return m_DebugName; }
	protected:
		const char *m_DebugName;
	};
}
