#pragma once

#include "Hazel/Core/Layer.h"

namespace Hazel
{
	class ImGuiLayer
		: public Layer
	{
	private:
		float m_time = 0.0f;

	public:
		void onAttach() override;
		void onDetach() override;

		void begin();
		void end();
	};
}
