#pragma once

#include <pch>

#include "Core.h"
#include <Reyes/Events/Event.h>
#include <Reyes/Events/WindowEvent.h>
#include <Reyes/RenderAPI/Context.h>

namespace Reyes {
	struct WindowProperties {
		std::string Title;
		glm::vec2 Size;

		explicit WindowProperties(std::string title = "Reyes Engine", glm::vec2 size = {1280, 720})
				: Title(std::move(title)), Size(size) {}
	};

	class  Window {
	public:
		using EventCallbackFn = std::function<void(Event &)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		[[nodiscard]] virtual const glm::vec2 &GetSize() const = 0;

		virtual void SetEventCallback(const EventCallbackFn &callback) = 0;

		virtual void SetVSync(bool enabled) = 0;
		[[nodiscard]] virtual bool IsVSync() const = 0;

		[[nodiscard]] virtual void *GetNativeWindow() const = 0;

		static Window *Create(const WindowProperties &props = WindowProperties());
	protected:
		Scope<RenderAPI::Context> m_Context;
	};
}