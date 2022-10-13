#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Hazel
{
	class HAZEL_API Layer
	{
	protected:
		std::string m_debugName;

	public:
		Layer(const std::string& name = "Layer")
			: m_debugName(name) { }
		virtual ~Layer() { }

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onRender() {}
		virtual void onEvent(Event& e) {}

		const std::string& getName() { return m_debugName; }
	};
}
