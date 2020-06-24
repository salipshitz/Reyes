#pragma once

#include <Reyes/RenderAPI/Context.h>

struct GLFWwindow;

namespace Reyes::RenderAPI {
	class REYES_API OpenGLContext : public Context {
	public:
		explicit OpenGLContext(GLFWwindow *windowHandle);
		
		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow *m_WindowHandle;
	};
}