#include "Shader.h"

#include <Reyes/Core.h>
#include <Reyes/Log.h>
#include <Reyes/Renderer.h>

#include <platform/opengl/OpenGLShader.h>

namespace Reyes::RenderAPI {
	Shader *Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::OPENGL:
				REY_CORE_TRACE("Created OpenGL Vertex Buffer")
				return new OpenGLShader(vertexSrc, fragmentSrc);
			case RendererAPI::NONE: REY_CORE_ASSERT(false, "No-Rendering branch not yet implemented")
		}
		return nullptr;
	}
}