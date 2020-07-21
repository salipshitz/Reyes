#pragma once

#include <Reyes/Core/Core.h>

namespace Reyes::RenderAPI {
	class BufferLayout;
	class VertexBuffer;
	class IndexBuffer;

	class  VertexArray {
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(Ref<VertexBuffer> buffer) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer) = 0;

		[[nodiscard]] virtual const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const = 0;
		[[nodiscard]] virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};
}