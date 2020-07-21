#include "pch"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

#include <Reyes/RenderAPI/Buffer.h>

namespace Reyes::RenderAPI {
	OpenGLVertexArray::OpenGLVertexArray() : m_ID(0) {
		glGenVertexArrays(1, &m_ID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_ID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_ID);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer> buffer) {
		glBindVertexArray(m_ID);
		buffer->Bind();
		const auto &layout = buffer->GetLayout();
		for (unsigned int i = 0; i < layout.GetElements().size(); i++) {
			const auto &element = layout.GetElements()[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.GetCount(), element.Type.ToGL(), element.Normalized,
			                      buffer->GetLayout().GetStride(), (const void *) element.Offset);
		}
		m_VertexBuffers.push_back(buffer);
	}
	
	void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer> buffer) {
		glBindVertexArray(m_ID);
		buffer->Bind();

		m_IndexBuffer = buffer;
	}
}