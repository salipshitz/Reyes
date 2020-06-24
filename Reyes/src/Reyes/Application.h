#pragma once

#include "ImGui/ImGuiLayer.h"
#include "Core.h"
#include "LayerStack.h"
#include "Renderer.h"

namespace Reyes {
	class Window;

	class WindowCloseEvent;
	
	class REYES_API Application {
	public:
		inline static Application &Get() { return *s_Instance; }

		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event &e);

		void PushLayer(Layer *layer) { m_LayerStack.PushLayer(layer); }
		void PushOverlay(Layer *overlay) { m_LayerStack.PushOverlay(overlay); }

		inline Window &GetWindow() { return *m_Window; }
	private:
		static Application *s_Instance;

		bool OnWindowClosed(WindowCloseEvent &e);

		Window *m_Window;
		ImGuiLayer *m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		
		Renderer *m_Renderer;
	};

	// Define in CLIENT
	Application *CreateApplication();
}