#pragma once

#include <utility>

#include "reypch.h"

#include "Core.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "RenderAPI/Context.h"

namespace Reyes {
	struct WindowProperties {
		std::string Title;
		unsigned int Width, Height;

		explicit WindowProperties(std::string title = "Reyes Engine", unsigned int width = 1280,
		                 unsigned int height = 720) : Title(std::move(title)), Width(width), Height(height) {}
	};

	class REYES_API Window {
	public:
		using EventCallbackFn = std::function<void(Event &)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		[[nodiscard]] virtual unsigned int GetWidth() const = 0;

		[[nodiscard]] virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn &callback) = 0;

		virtual void SetVSync(bool enabled) = 0;

		[[nodiscard]] virtual bool IsVSync() const = 0;

		static Window *Create(const WindowProperties &props = WindowProperties());

		[[nodiscard]] virtual void *GetNativeWindow() const = 0;
	protected:
		RenderAPI::Context *m_Context;
	};
}