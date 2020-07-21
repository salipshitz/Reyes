#include <pch>

#include "API.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"

#include <Reyes/Core/Core.h>
#include <Reyes/Core/Log.h>

#include <Platform/OpenGL/OpenGLAPI.h>
#include <Platform/OpenGL/OpenGLVertexArray.h>
#include <Platform/OpenGL/OpenGLBuffer.h>
#include <Platform/OpenGL/OpenGLShader.h>
#include <Platform/OpenGL/OpenGLTexture.h>

namespace Reyes::RenderAPI {
	API::Type API::s_API = API::OPENGL;

	Ref<VertexArray> VertexArray::Create() {
		switch (API::GetAPI()) {
			case API::OPENGL:
				REY_CORE_TRACE("Created OpenGL Vertex Array");
				return std::make_shared<OpenGLVertexArray>();
			default:
				REY_CORE_ASSERT(false, "Error: Undefined Rendering branch");
		}
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(void *vertices, size_t size, BufferLayout layout) {
		switch (API::GetAPI()) {
			case API::OPENGL:
				REY_CORE_TRACE("Created OpenGL Vertex Buffer");
				return std::make_shared<OpenGLVertexBuffer>(vertices, size, std::move(layout));
			default:
				REY_CORE_ASSERT(false, "No-Rendering branch not yet implemented");
		}
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(unsigned int *vertices, unsigned int size) {
		switch (API::GetAPI()) {
			case API::OPENGL:
				REY_CORE_TRACE("Created OpenGL Index Buffer");
				return std::make_shared<OpenGLIndexBuffer>(vertices, size);
			default:
				REY_CORE_ASSERT(false, "Error: Undefined Rendering branch");
		}
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc) {
		switch (API::GetAPI()) {
			case API::OPENGL:
				REY_CORE_TRACE("Created OpenGL Shader");
				return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
			default:
				REY_CORE_ASSERT(false, "Error: Undefined Rendering branch");
		}
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string &path) {
		switch (API::GetAPI()) {
			case API::OPENGL:
				REY_CORE_TRACE("Created OpenGL Texture");
				return std::make_shared<OpenGLShader>(path);
			default:
			REY_CORE_ASSERT(false, "Error: Undefined Rendering branch");
		}
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const char *path, bool minNearest, bool magNearest) {
		switch (API::GetAPI()) {
			case API::OPENGL:
				REY_CORE_TRACE("Created OpenGL Texture 2D");
				return std::make_shared<OpenGLTexture2D>(path, minNearest, magNearest);
			default:
				REY_CORE_ASSERT(false, "Error: Undefined Rendering branch");
		}
		return nullptr;
	}

	Ref<AtlasTexture> AtlasTexture::Create(const char *path, int size) {
		switch (API::GetAPI()) {
			case API::OPENGL:
				REY_CORE_TRACE("Created OpenGL Atlas Texture");
				return std::make_shared<OpenGLAtlasTexture>(path, size);
			default:
				REY_CORE_ASSERT(false, "Error: Undefined Rendering branch");
		}
		return nullptr;
	}
}