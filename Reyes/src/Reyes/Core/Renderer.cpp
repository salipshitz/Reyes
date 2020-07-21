#include <pch>
#include "Renderer.h"

#include "Log.h"

#include <Reyes/Transform.h>
#include <Reyes/Camera.h>
#include <Reyes/RenderAPI/Shader.h>

#include <Platform/OpenGL/OpenGLAPI.h>
#include <Platform/OpenGL/OpenGLShader.h>

namespace Reyes
{
	RenderAPI::API *Renderer::s_API;
	glm::mat4 Renderer::s_VPMatrix(1.f);

	void Renderer::Init()
	{
		using namespace RenderAPI;

		REY_CORE_TRACE("API: {}", API::GetAPI() == API::OPENGL);
		switch (API::GetAPI())
		{
		case API::OPENGL:
			s_API = new OpenGLAPI;
			break;
		default:
			REY_CORE_ASSERT(false, "Error: unknown API");
		}
	}

	void Renderer::BeginScene(Ref<Camera> camera)
	{
		s_VPMatrix = camera->GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<RenderAPI::VertexArray> &vertexArray, Ref<Transform> transform,
						  Ref<RenderAPI::Shader> &shader)
	{
		shader->Bind();
		std::dynamic_pointer_cast<RenderAPI::OpenGLShader>(shader)->SetUniform("u_ViewProjection",
																			   s_VPMatrix); // TODO: Batch Rendering
		std::dynamic_pointer_cast<RenderAPI::OpenGLShader>(shader)->SetUniform("u_Model",
																			   transform->GetTransformMatrix());

		vertexArray->Bind();
		s_API->DrawIndexed(vertexArray);
	}

	void Renderer::SetViewport(glm::vec2 size)
	{
		s_API->SetViewport(size);
	}
} // namespace Reyes