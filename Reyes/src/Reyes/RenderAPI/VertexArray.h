#pragma once

namespace Reyes::RenderAPI {
	class VertexArray {
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void Enable(unsigned int index, unsigned int count) = 0;

		static VertexArray *Create();
	};
}