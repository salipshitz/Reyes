#pragma once

#include "Core.h"

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <Reyes/RenderAPI/API.h>

namespace Reyes {
	namespace RenderAPI {
		class VertexArray;
		class Shader;
	}
	class Camera;
	class Transform;

	class  Renderer {
	public:
		static void Init();

		static void BeginScene(Ref<Camera> camera);
		static void EndScene();

		static void Submit(const Ref<RenderAPI::VertexArray> &vertexArray, Ref<Transform> transform,
		                   Ref<RenderAPI::Shader> &shader);

		inline static void SetClearColor(const glm::vec4 &color) { s_API->SetClearColor(color); }
		inline static void Clear() { s_API->Clear(); }

		static void SetViewport(glm::vec2 size);

	private:
		static RenderAPI::API *s_API;
		static glm::mat4 s_VPMatrix;
	};
}