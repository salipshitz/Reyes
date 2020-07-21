#pragma once

#include <Reyes/RenderAPI/VertexArray.h>

namespace Reyes::RenderAPI {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(Ref<VertexBuffer> buffer) override;
		void SetIndexBuffer(Ref<IndexBuffer> buffer) override;

		[[nodiscard]] inline const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const override {
			return m_VertexBuffers;
		}
		[[nodiscard]] inline Ref<IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; };

	private:
		unsigned int m_ID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}
