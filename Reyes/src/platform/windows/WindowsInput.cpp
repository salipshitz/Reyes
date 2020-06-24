#include "reypch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include <Reyes/Application.h>
#include <Reyes/Window.h>

namespace Reyes {
	Input *Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode) {
		auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, REY_KEY_TO_GLFW(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Reyes::WindowsInput::IsMouseButtonPressedImpl(int button) {
		auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, REY_MB_TO_GLFW(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 WindowsInput::GetMousePositionImpl() {
		auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return {xpos, ypos};
	}

	float Reyes::WindowsInput::GetMouseXImpl() {
		return GetMousePositionImpl().x;
	}

	float Reyes::WindowsInput::GetMouseYImpl() {
		return GetMousePositionImpl().y;
	}
}
