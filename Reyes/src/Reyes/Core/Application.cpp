#include <pch>
#include "Application.h"

#include "Window.h"
#include "Log.h"

#include "Renderer.h"

#include <GLFW/glfw3.h>

namespace Reyes {
	Application *Application::s_Instance = nullptr;

	Application::Application() {
		REY_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window.reset(Window::Create());
		m_Window->SetEventCallback(REY_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);

		Renderer::SetClearColor({1.f, 0.f, 1.f, 1.f});
	}

	Application::~Application() = default;

	void Application::Run() {
		auto lastTime = (float) glfwGetTime();
		while (m_Running) {
			auto time = (float) glfwGetTime();

			Render();

			for (const auto &layer : m_LayerStack)
				layer->OnUpdate(time - lastTime);

			m_ImGuiLayer->Begin();
			for (const auto &layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
			lastTime = time;
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