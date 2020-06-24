#pragma once

namespace Reyes::RenderAPI {
	class Buffer {
	public:
		virtual ~Buffer() = default;
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		[[nodiscard]] virtual inline unsigned int GetCount() const = 0;
		
		static Buffer *CreateVertex(float *vertices, unsigned int size);
		static Buffer *CreateIndex(unsigned int *vertices, unsigned int size);
	};
}