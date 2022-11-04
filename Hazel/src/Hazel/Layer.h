#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Core/Timestep.h"

namespace Hazel
{
	class HAZEL_API Layer
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
		virtual void onRender() {}
		virtual void onEvent(Event& e) {}

		const std::string& getName() { return m_debugName; }
	};
}
