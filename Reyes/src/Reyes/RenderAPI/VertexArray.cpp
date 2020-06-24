#include "VertexArray.h"

#include <Reyes/Renderer.h>
#include <Reyes/Core.h>
#include <Reyes/Log.h>

#include <platform/opengl/OpenGLVertexArray.h>

namespace Reyes::RenderAPI {
	VertexArray *VertexArray::Create() {
		switch (Renderer::GetAPI()) {
			case RendererAPI::OPENGL:
				REY_CORE_TRACE("Created OpenGL Vertex Array")
				return new OpenGLVertexArray();
			case RendererAPI::NONE: REY_CORE_ASSERT(false, "No-Rendering branch not yet implemented")
		}
		return nullptr;
	}
}
