#include "tpch.h"
#include "layer_stack.h"

namespace teris {

	LayerStack::LayerStack() {
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers) {
			layer->on_detach();
			delete layer;
		}
	}

	void LayerStack::push_layer(Layer* layer) {
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
		layer->on_attach();
	}

	void LayerStack::push_overlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
		overlay->on_attach();
	}

	void LayerStack::pop_layer(Layer* layer) {
		layer->on_detach();
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}

	void LayerStack::pop_overlay(Layer* layer) {
		layer->on_detach();
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}
	}
}