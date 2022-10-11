#pragma once

#include "Hazel/Input.h"

namespace Hazel
{
	class WindowsInput
		: public Input
	{
	private:
		bool isKeyPressedImpl(int keycode) override;

		bool isMouseButtonPressedImpl(int button) override;
		std::pair<float, float> getMousePositionImpl() override;
		float getMousePositionX() override;
		float getMousePositionY() override;
	};
}
