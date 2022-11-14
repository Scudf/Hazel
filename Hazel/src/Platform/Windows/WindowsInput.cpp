#include "hzpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

#include "Hazel/Core/Application.h"

namespace Hazel
{
	Scope<Input> Input::s_instance = MakeScope<WindowsInput>();

	bool WindowsInput::isKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::isMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);

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
