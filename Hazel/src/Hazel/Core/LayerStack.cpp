#include "hzpch.h"

#include "Hazel/Core/LayerStack.h"

namespace Hazel
{
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
		{
			layer->onDetach();
			delete layer;
		}
	}

	void Hazel::LayerStack::pushLayer(Layer* layer)
	{
		m_layers.emplace(begin() + m_layerInsertIndex, layer);
		++m_layerInsertIndex;
	}

	void Hazel::LayerStack::pushOverlay(Layer* overlay)
	{
		m_layers.push_back(overlay);
	}

	void Hazel::LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(begin(), end() + m_layerInsertIndex, layer);
		if (it != m_layers.begin() + m_layerInsertIndex)
		{
			layer->onDetach();
			m_layers.erase(it);
			--m_layerInsertIndex;
		}
	}

	void Hazel::LayerStack::popOverlay(Layer* overlay)
	{
		auto it = std::find(begin() + m_layerInsertIndex, end(), overlay);
		if (it != end())
		{
			overlay->onDetach();
			m_layers.erase(it);
		}
	}
}
