#pragma once

namespace Hazel
{
	class Input
	{
	private:
		static Scope<Input> s_instance;

	protected:
		Input() = default;

		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> getMousePositionImpl() = 0;
		virtual float getMousePositionX() = 0;
		virtual float getMousePositionY() = 0;

	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		static bool IsKeyPressed(int keycode) { return s_instance->isKeyPressedImpl(keycode); }

		static bool IsMouseButton(int button) { return s_instance->isMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return s_instance->getMousePositionImpl(); }
		static float GetMousePositionX() { return s_instance->getMousePositionX(); }
		static float GetMousePositionY() { return s_instance->getMousePositionY(); }
	};
}