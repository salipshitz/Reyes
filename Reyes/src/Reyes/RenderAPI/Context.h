#pragma once

#include <Reyes/Core.h>

namespace Reyes::RenderAPI {
	using namespace Reyes;
	class REYES_API Context {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
