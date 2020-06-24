#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Reyes::RenderAPI {
	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}
	
	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);
	}
	
	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
	}
	
	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::Enable(unsigned int index, unsigned int count) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, count, GL_FLOAT, false, 0, nullptr);
	}
}