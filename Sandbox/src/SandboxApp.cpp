#include <Hazel.h>

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		pushLayer(new Hazel::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}
