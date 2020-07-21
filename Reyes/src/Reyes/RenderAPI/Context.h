#pragma once

#include <Reyes/Core/Core.h>

namespace Reyes::RenderAPI {
	using namespace Reyes;
	class  Context {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
