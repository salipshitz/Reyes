#pragma once
#include "reypch.h"

#include "Reyes/Core.h"

namespace Reyes {
	class Event;
	
	class REYES_API Layer {
	public:
		explicit Layer(std::string name = "Layer") : m_DebugName(std::move(name)) {}
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event &event) {}

		[[nodiscard]] inline const std::string &GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}
