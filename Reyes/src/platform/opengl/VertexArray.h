#pragma once

namespace Renderer {
	class VertexBuffer;
	class VertexBufferLayout;

	class OpenGLVertexArray {
		unsigned int m_ID;

	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const;
		static void Unbind();

		void AddBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout) const;
	};
}
