#pragma once

#include <Reyes/RenderAPI/Buffer.h>

namespace Reyes::RenderAPI
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void *vertices, size_t size, BufferLayout layout);
		~OpenGLVertexBuffer() override;

		[[nodiscard]] inline const BufferLayout &GetLayout() const override { return m_Layout; }

		void Bind() const override;
		void Unbind() const override;

		void SetData(void *vertices, size_t size) override;

	private:
		unsigned int m_ID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int *indices, unsigned int size);
		~OpenGLIndexBuffer() override;

		[[nodiscard]] inline unsigned int GetCount() const override
		{
			return m_Count;
		}

		void Bind() const override;
		void Unbind() const override;

	private:
		unsigned int m_ID;
		unsigned int m_Count;
	};
} // namespace Reyes::RenderAPI