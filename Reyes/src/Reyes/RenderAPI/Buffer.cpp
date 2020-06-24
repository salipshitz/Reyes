#include "reypch.h"
#include "Buffer.h"

#include <Reyes/Renderer.h>
#include <Reyes/Core.h>
#include <Reyes/Log.h>

#include <platform/opengl/OpenGLBuffer.h>

namespace Reyes::RenderAPI {
	Buffer *Buffer::CreateVertex(float *vertices, unsigned int size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::OPENGL:
				REY_CORE_TRACE("Created OpenGL Vertex Buffer")
				return new OpenGLVertexBuffer(vertices, size);
			case RendererAPI::NONE: REY_CORE_ASSERT(false, "No-Rendering branch not yet implemented")
		}
		return nullptr;
	}

	Buffer *Buffer::CreateIndex(unsigned int *vertices, unsigned int size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::OPENGL:
				REY_CORE_TRACE("Created OpenGL Vertex Buffer")
				return new OpenGLIndexBuffer(vertices, size);
			case RendererAPI::NONE: REY_CORE_ASSERT(false, "No-Rendering branch not yet implemented")
		}
		return nullptr;
	}
}