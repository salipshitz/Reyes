#pragma once

#include <pch>
#include "Core.h"
#include "Layer.h"

namespace Reyes {
	class  LayerStack {
	public:
		LayerStack() = default;
		~LayerStack() = default;

		void PushLayer(Layer *layer);
		void PopLayer(Layer *layer);
		void PushOverlay(Layer *overlay);
		void PopOverlay(Layer *overlay);

		inline std::vector<Layer *>::iterator begin() { return m_Layers.begin(); }
		inline std::vector<Layer *>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer *> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}