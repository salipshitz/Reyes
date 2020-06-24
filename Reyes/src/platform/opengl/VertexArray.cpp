#include "VertexArray.h"

#include <glad/glad.h>

#include <Reyes/RenderAPI/VertexBuffer.h>
#include <Reyes/RenderAPI/VertexBufferLayout.h>

namespace Renderer {
	OpenGLVertexArray::OpenGLVertexArray() : m_ID(0) {
		glGenVertexArrays(1, &m_ID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_ID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_ID);
	}

	void OpenGLVertexArray::Unbind() {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout) const {
		Bind();
		buffer.Bind();
		const auto &elements = layout.GetElements();
		size_t offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto &element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),
			                      (const void *) offset);
			offset += element.count * VertexLayoutElement::GetSizeOfType(element.type);
		}
	}
}