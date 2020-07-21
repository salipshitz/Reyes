#pragma once

#include <Reyes/Core/Core.h>
#include <Reyes/RenderAPI/API.h>
#include <Reyes/RenderAPI/VertexArray.h>

namespace Reyes::RenderAPI {
	class OpenGLAPI : public API {
	public:
		OpenGLAPI();
		
		void SetClearColor(const glm::vec4 &color) override;
		void Clear() override;
		void DrawIndexed(const Ref<VertexArray> &vertexArray) override;
		void SetViewport(glm::vec2 size);
	};
}
