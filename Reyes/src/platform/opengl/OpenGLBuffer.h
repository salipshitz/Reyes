#pragma once

#include "Reyes/RenderAPI/Buffer.h"

namespace Reyes::RenderAPI {
	class OpenGLVertexBuffer : public Buffer {
	public:
		OpenGLVertexBuffer(float *vertices, unsigned int size);
		~OpenGLVertexBuffer() override;

		[[nodiscard]] inline unsigned int GetCount() const override { return m_Count; }

		void Bind() const override;
		void Unbind() const override;
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};

	class OpenGLIndexBuffer : public Buffer {
	public:
		OpenGLIndexBuffer(unsigned int *indices, unsigned int size);
		~OpenGLIndexBuffer() override;

		[[nodiscard]] inline unsigned int GetCount() const override { return m_Count; }

		void Bind() const override;
		void Unbind() const override;
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};
}