#include "pch"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Reyes/Core/Log.h>

namespace Reyes::RenderAPI {
	OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : m_WindowHandle(windowHandle) {
		REY_CORE_ASSERT(windowHandle, "Window Handle is null");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		REY_CORE_ASSERT(status, "Failed to initialize GLAD");

		REY_CORE_INFO("OpenGL Hardware Info:");
		REY_CORE_INFO("    Vendor: {}", glGetString(GL_VENDOR));
		REY_CORE_INFO("    Renderer: {}", glGetString(GL_RENDERER));
		REY_CORE_INFO("    Version: {}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}