#include "pch"
#include "OpenGLAPI.h"

#include <glad/glad.h>

#include <Reyes/RenderAPI/Buffer.h>

#define GL_CALL(func) {func REY_CORE_LOG(#func+" at {}", __LINE__)}

namespace Reyes::RenderAPI {
	OpenGLAPI::OpenGLAPI() {
#ifdef REY_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(
				[](unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length,
				   const char *message, const void *userParam) {
					if (type == GL_DEBUG_TYPE_OTHER) // Ignore NVIDIA warning about video memory
						return;
					if (type == GL_DEBUG_TYPE_ERROR)
						REY_CORE_ERROR("OpenGL Error (Type: {}): {}", type, message);
					else
						REY_CORE_WARN("OpenGL Warning (Type: {}): {}", type, message);
				}, nullptr);
#endif
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_CULL_FACE);
	}

	void OpenGLAPI::SetClearColor(const glm::vec4 &color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLAPI::DrawIndexed(const Ref<VertexArray> &vertexArray) {
		// glPointSize(5.f);
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}