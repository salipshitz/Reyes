#include "pch"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

#include <utility>

namespace Reyes::RenderAPI
{
	unsigned int ShaderDataType::ToGL() const
	{
		switch (m_Value)
		{
		case Float:
		case Float2:
		case Float3:
		case Float4:
		case Mat3:
		case Mat4:
			return GL_FLOAT;
		case Int:
		case Int2:
		case Int3:
		case Int4:
			return GL_INT;
		case Bool:
			return GL_BOOL;
		default:
			REY_CORE_ASSERT(false, "Unknown ShaderDataType");
			return 0;
		}
	}

	// Vertex Buffer ///////////////////////////////////////////////////////////////////////////
	OpenGLVertexBuffer::OpenGLVertexBuffer(void *vertices, size_t size, BufferLayout layout)
		: m_Layout(std::move(layout)), m_ID(0)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	void OpenGLVertexBuffer::SetData(void *vertices, size_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// Index Buffer ////////////////////////////////////////////////////////////////////////////////
	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int *indices, unsigned int size)
		: m_Count(size / sizeof(unsigned int))
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
} // namespace Reyes::RenderAPI