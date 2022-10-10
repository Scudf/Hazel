#pragma once

#include "Hazel/Layer.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/ApplicationEvent.h"

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
		void onUpdate() override;
		void onEvent(Event& e) override;

		bool onMouseMoved(MouseMovedEvent& e);
		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onMouseButtonPressed(MouseButtonPressedEvent& e);
		bool onMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool onKeyPressed(KeyPressedEvent& e);
		bool onKeyReleased(KeyReleasedEvent& e);
		bool onKeyTyped(KeyTypedEvent& e);
		bool onWindowResized(WindowResizedEvent& e);
	};
}
