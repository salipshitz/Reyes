#pragma once

namespace Reyes {
	namespace RenderAPI {
		class Buffer;
		class Shader;
		class VertexArray;
	}
	enum class RendererAPI {
		NONE = 0, OPENGL
	};

	class Renderer {
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
		
		Renderer();
		~Renderer();
		
		void Render();
	private:
		static RendererAPI s_RendererAPI;

		RenderAPI::VertexArray *m_VertexArray;

		RenderAPI::Buffer *m_VertexBuffer, *m_IndexBuffer;
		RenderAPI::Shader *m_Shader;
	};
}