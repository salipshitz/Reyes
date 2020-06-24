#pragma once

#include <Reyes/RenderAPI/Shader.h>

namespace Reyes::RenderAPI {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);

		~OpenGLShader() override;
		void Bind() const override;
		void Unbind() const override;
		
	private:
		unsigned int m_RendererID;
	};
}
