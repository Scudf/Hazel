#include "hzpch.h"

#include "LayerStack.h"

namespace Hazel
{
	LayerStack::LayerStack()
	{
		m_layerInsert = m_layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
			delete layer;
	}

	void Hazel::LayerStack::pushLayer(Layer* layer)
	{
		m_layerInsert = m_layers.emplace(m_layerInsert, layer);
	}

	void Hazel::LayerStack::pushOverlay(Layer* overlay)
	{
		m_layers.push_back(overlay);
	}

	void Hazel::LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(begin(), end(), layer);
		if (it != end())
		{
			m_layers.erase(it);
			--m_layerInsert;
		}
	}

	void Hazel::LayerStack::popOverlay(Layer* overlay)
	{
		auto it = std::find(begin(), end(), overlay);
		if (it != end())
			m_layers.erase(it);
	}
}
