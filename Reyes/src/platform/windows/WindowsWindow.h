#pragma once

#include <Reyes/Window.h>

struct GLFWwindow;

namespace Reyes {
	class WindowsWindow : public Window {
	public:
		explicit WindowsWindow(const WindowProperties &props);
		~WindowsWindow() override;

		void OnUpdate() override;

		[[nodiscard]] inline unsigned int GetWidth() const override { return m_Data.Width; };
		[[nodiscard]] inline unsigned int GetHeight() const override { return m_Data.Height; };

		inline void SetEventCallback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }

		void SetVSync(bool enabled) final;
		[[nodiscard]] inline bool IsVSync() const final { return m_Data.VSync; }

		[[nodiscard]] inline void *GetNativeWindow() const override { return m_Window; }

	private:
		GLFWwindow *m_Window;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
