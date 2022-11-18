#include "hzpch.h"
#include "Platform/Windows/WindowsInput.h"

#include <GLFW/glfw3.h>

#include "Hazel/Core/Application.h"

namespace Hazel
{
	Scope<Input> Input::s_instance = MakeScope<WindowsInput>();

	bool WindowsInput::isKeyPressedImpl(KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, (int32_t)keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::isMouseButtonPressedImpl(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, (int32_t)button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::getMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().getWindow().getNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return { (float)x, (float)y };
	}

	float WindowsInput::getMousePositionX()
	{
		auto [x, y] = getMousePositionImpl();
		return x;
	}

	float WindowsInput::getMousePositionY()
	{
		auto [x, y] = getMousePositionImpl();
		return y;
	}
}
