#pragma once

#include <Reyes/ImGui/ImGuiLayer.h>

#include <utility>
#include "Core.h"
#include "LayerStack.h"

namespace Reyes {
	class Window;
	class WindowCloseEvent;
	class KeyEvent;

	class  Application {
	public:
		inline static Application &Get() { return *s_Instance; }

		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event &e);

		void PushLayer(Layer *layer) { m_LayerStack.PushLayer(layer); }
		void PushOverlay(Layer *overlay) { m_LayerStack.PushOverlay(overlay); }

		inline Window &GetWindow() { return *m_Window; }

		virtual void Render() = 0;

	private:
		static Application *s_Instance;

		bool OnWindowClosed(WindowCloseEvent &e);

		Ref<Window> m_Window;
		ImGuiLayer *m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// Define in CLIENT
	Application *CreateApplication();
}