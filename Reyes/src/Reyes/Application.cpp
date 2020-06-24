#include "reypch.h"
#include "Application.h"

#include "Window.h"
#include "Log.h"

namespace Reyes {
	Application *Application::s_Instance = nullptr;

	Application::Application() {
		REY_CORE_ASSERT(!s_Instance, "Application already exists")
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(REY_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		
		m_Renderer = new Renderer();
	}

	Application::~Application() {
		delete m_ImGuiLayer;
		delete m_Renderer;
	}

	void Application::Run() {
		while (m_Running) {
			m_Renderer->Render();

			for (Layer *layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer *layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();


			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event &e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(REY_BIND_EVENT_FN(Application::OnWindowClosed));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent &e) {
		m_Running = false;
		return true;
	}
}