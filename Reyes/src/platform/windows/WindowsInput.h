#pragma once

#include <Reyes/Input.h>

namespace Reyes {
	class WindowsInput : public Input {
	protected:
		[[nodiscard]] bool IsKeyPressedImpl(int keycode) override;
		[[nodiscard]] bool IsMouseButtonPressedImpl(int button) override;

		[[nodiscard]] float GetMouseXImpl() override;
		[[nodiscard]] float GetMouseYImpl() override;
		[[nodiscard]] glm::vec2 GetMousePositionImpl() override;
	};
}