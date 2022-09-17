#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Hello World!");
	HZ_INFO("My name is Vas!");

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif
