#pragma once

#include <pch>

namespace Reyes {
	namespace RenderAPI {
		class Shader;
	}
	class Material {
		
	private:
		Ref<RenderAPI::Shader> m_Shader;
	};
}