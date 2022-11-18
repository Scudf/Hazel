#pragma once

#include "Hazel/Core/Input.h"

namespace Hazel
{
	class WindowsInput
		: public Input
	{
	private:
		bool isKeyPressedImpl(KeyCode keycode) override;

		bool isMouseButtonPressedImpl(MouseCode button) override;
		std::pair<float, float> getMousePositionImpl() override;
		float getMousePositionX() override;
		float getMousePositionY() override;
	};
}
