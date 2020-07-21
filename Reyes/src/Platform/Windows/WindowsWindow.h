#pragma once

#include <Reyes/Core/Window.h>

struct GLFWwindow;

namespace Reyes
{
	class WindowsWindow : public Window
	{
	public:
		explicit WindowsWindow(const WindowProperties &props);
		~WindowsWindow() override;

		void OnUpdate() override;

		[[nodiscard]] inline const glm::vec2 &GetSize() const override { return m_Data.Size; }

		inline void SetEventCallback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }

		void SetVSync(bool enabled) final;
		[[nodiscard]] inline bool IsVSync() const final { return m_Data.VSync; }

		[[nodiscard]] inline void *GetNativeWindow() const override { return m_Window; }

	private:
		GLFWwindow *m_Window;

		struct WindowData
		{
			std::string Title;
			glm::vec2 Size;
			bool VSync;

			EventCallbackFn EventCallback;
		} m_Data;
	};
} // namespace Reyes
