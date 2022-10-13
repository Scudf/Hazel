#pragma once

#include "Hazel/Layer.h"

namespace Hazel
{
	class HAZEL_API ImGuiLayer
		: public Layer
	{
	private:
		float m_time = 0.0f;

	public:
		void onAttach() override;
		void onDetach() override;
		void onRender() override;

		void begin();
		void end();
	};
}
