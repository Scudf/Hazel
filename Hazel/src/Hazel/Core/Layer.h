#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Core/Timestep.h"

namespace Hazel
{
	class Layer
	{
	protected:
		std::string m_debugName;

	public:
		Layer(const std::string& name = "Layer")
			: m_debugName(name) { }
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(Timestep ts) {}
		virtual void onImGUIRender() {}
		virtual void onEvent(Event& e) {}

		const std::string& getName() { return m_debugName; }
	};
}
