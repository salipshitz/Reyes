#pragma once

#include <Reyes/RenderAPI/VertexArray.h>

namespace Reyes::RenderAPI {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;
		
		void Bind() const override;
		void Unbind() const override;
		
		void Enable(unsigned int index, unsigned int count) override;
		
	private:
		unsigned int m_RendererID;
	};
}
