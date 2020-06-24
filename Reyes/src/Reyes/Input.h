#pragma once

#include "Core.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"
#include <glm/vec2.hpp>

namespace Reyes {
	class REYES_API Input {
	public:
		[[nodiscard]] inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		[[nodiscard]] inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		[[nodiscard]] inline static glm::vec2 GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		[[nodiscard]] inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		[[nodiscard]] inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;

		virtual glm::vec2 GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

		static Input *s_Instance;
	};
}