#pragma once

#include <Reyes/Layer.h>

namespace Reyes {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() override;

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();

		float m_Time = 0.f;
	};
}