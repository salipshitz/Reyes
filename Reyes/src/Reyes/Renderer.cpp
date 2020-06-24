#include "reypch.h"
#include "Renderer.h"

#include <glad/glad.h>

#include "RenderAPI/Buffer.h"
#include "RenderAPI/VertexArray.h"
#include "RenderAPI/Shader.h"

namespace Reyes {
	RendererAPI Renderer::s_RendererAPI = RendererAPI::OPENGL;

	Renderer::Renderer() {
		m_VertexArray = RenderAPI::VertexArray::Create();

		float vertices[3 * 3] = {-0.5f, -0.5f, 0.f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,};
		m_VertexBuffer = RenderAPI::Buffer::CreateVertex(vertices, sizeof(vertices));
	
		m_VertexArray->Enable(0, 3);

		unsigned int indices[3] = {0, 1, 2};
		m_IndexBuffer = RenderAPI::Buffer::CreateIndex(indices, sizeof(indices));

		std::string vertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 i_Position;
out vec3 v_Position;

void main() {
	v_Position = i_Position;
	gl_Position = vec4(i_Position, 1.0);
}
)";

		std::string fragmentSrc = R"(
#version 330 core

layout(location = 0) out vec4 o_Color;
in vec3 v_Position;

void main() {
	o_Color = vec4(v_Position * 0.5 + 0.5, 1.0);
}
)";

		m_Shader = RenderAPI::Shader::Create(vertexSrc, fragmentSrc);
	}

	Renderer::~Renderer() {
		delete m_VertexBuffer;
		delete m_IndexBuffer;
		delete m_Shader;
	}

	void Renderer::Render() {
		glClearColor(0.1f, 0.1f, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		m_Shader->Bind();

		m_VertexArray->Bind();
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}