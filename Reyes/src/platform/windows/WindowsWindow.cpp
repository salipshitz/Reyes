#include "WindowsWindow.h"

#include <GLFW/glfw3.h>

#include <Reyes/Input.h>
#include <Reyes/Log.h>

#include <Reyes/Events/MouseEvent.h>
#include <Reyes/Events/KeyEvent.h>

#include <platform/opengl/OpenGLContext.h>

namespace Reyes {
	static bool s_GLFWInitialized = false;

	Window *Window::Create(const WindowProperties &props) {
		return new WindowsWindow(props);
	}

	static void GLFWErrorCallback(int error, const char *description) {
		REY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProperties &props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		
		REY_CORE_INFO("Creating window {0}: Width = {1}, Height = {2}");
		
		if (!s_GLFWInitialized) {
			int success = glfwInit();
			REY_CORE_ASSERT(success, "Could not initialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}
		
		m_Window = glfwCreateWindow((int) props.Width, (int) props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = new RenderAPI::OpenGLContext(m_Window);
		m_Context->Init();
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS: {
					KeyDownEvent event(REY_KEY_FROM_GLFW(key));
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyUpEvent event(REY_KEY_FROM_GLFW(key));
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyRepeatEvent event(REY_KEY_FROM_GLFW(key), 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int key) {
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
			KeyTypeEvent event(REY_KEY_FROM_GLFW(key));
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS: {
					MouseDownEvent event(REY_MB_FROM_GLFW(button));
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseUpEvent event(REY_MB_FROM_GLFW(button));
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
			MouseScrollEvent event(xOffset, yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double x, double y) {
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
			MouseMoveEvent event(x, y);
			data.EventCallback(event);
		});
	}

	WindowsWindow::~WindowsWindow() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled) {
		glfwSwapInterval(enabled);
		m_Data.VSync = enabled;
	}
}
