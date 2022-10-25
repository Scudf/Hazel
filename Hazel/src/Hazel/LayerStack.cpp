#include "hzpch.h"

#include "LayerStack.h"

namespace Hazel
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
			delete layer;
	}

	void Hazel::LayerStack::pushLayer(Layer* layer)
	{
		m_layers.emplace(begin() + m_layerInsertIndex, layer);
		++m_layerInsertIndex;
		layer->onAttach();
	}

	void Hazel::LayerStack::pushOverlay(Layer* overlay)
	{
		m_layers.push_back(overlay);
		overlay->onAttach();
	}

	void Hazel::LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(begin(), end(), layer);
		if (it != end())
		{
			layer->onDetach();
			m_layers.erase(it);
			--m_layerInsertIndex;
		}
	}

	void Hazel::LayerStack::popOverlay(Layer* overlay)
	{
		auto it = std::find(begin(), end(), overlay);
		if (it != end())
		{
			overlay->onDetach();
			m_layers.erase(it);
		}
	}
}
