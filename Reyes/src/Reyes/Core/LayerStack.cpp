#include "LayerStack.h"

namespace Reyes {
	void LayerStack::PushLayer(Layer *layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex++, layer);
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer *overlay) {
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer *layer) {
		auto it = std::find(begin(), end(), layer);
		if (it != end()) {
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
		layer->OnDetach();
	}

	void LayerStack::PopOverlay(Layer *overlay) {
		auto it = std::find(begin(), end(), overlay);
		if (it != end())
			m_Layers.erase(it);
		overlay->OnDetach();
	}
}