#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseCodes.h"

namespace Hazel
{
	class Input
	{
	private:
		static Scope<Input> s_instance;

	protected:
		Input() = default;

		virtual bool isKeyPressedImpl(KeyCode keycode) = 0;
		virtual bool isMouseButtonPressedImpl(MouseCode button) = 0;
		virtual std::pair<float, float> getMousePositionImpl() = 0;
		virtual float getMousePositionX() = 0;
		virtual float getMousePositionY() = 0;

	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		static Scope<Input> Create();

		static bool IsKeyPressed(KeyCode keycode) { return s_instance->isKeyPressedImpl(keycode); }

		static bool IsMouseButton(MouseCode button) { return s_instance->isMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return s_instance->getMousePositionImpl(); }
		static float GetMousePositionX() { return s_instance->getMousePositionX(); }
		static float GetMousePositionY() { return s_instance->getMousePositionY(); }
	};
}