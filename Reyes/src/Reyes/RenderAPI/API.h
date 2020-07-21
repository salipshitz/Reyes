#pragma once

#include <Reyes/Core/Core.h>
#include <glm/vec4.hpp>

namespace Reyes::RenderAPI {
	class VertexArray;

	class API {
	public:
		enum Type {
			NONE = 0, OPENGL
		};

		virtual void SetClearColor(const glm::vec4 &color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref <VertexArray> &vertexArray) = 0;
	
		[[nodiscard]] inline static Type GetAPI() { return s_API; }
	private:
		static Type s_API;
	};
}