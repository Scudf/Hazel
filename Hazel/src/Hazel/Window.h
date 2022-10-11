#pragma once

#include "hzpch.h"

#include "Core.h"
#include "Events/Event.h"

namespace Hazel
{
	struct WindowProps
	{
		std::string title;
		unsigned int width, height;

		WindowProps(const std::string& _title = "Hazel Engine",
			unsigned int _width = 1280,
			unsigned int _height = 720)
			: title(_title), width(_width), height(_height)
		{

		}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual unsigned getWidth() const = 0;
		virtual unsigned getHeight() const = 0;

		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());

		virtual void* getNativeWindow() const = 0;
	};
}
