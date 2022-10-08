#pragma once

#include "Layer.h"

namespace Hazel
{
	using layer_it = std::vector<Layer*>::iterator;

	class HAZEL_API LayerStack
	{
	private:
		std::vector<Layer*> m_layers;
		layer_it m_layerInsert;

	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		layer_it begin() { return m_layers.begin(); }
		layer_it end() { return m_layers.end(); }
	};
}
