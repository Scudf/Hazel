#pragma once

#include "hzpch.h"

#include "Hazel/Core/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel
{
	struct WindowProps
	{
		std::string title;
		uint32_t width, height;

		WindowProps(const std::string& _title = "Hazel Engine",
			uint32_t _width = 1280,
			uint32_t _height = 720)
			: title(_title), width(_width), height(_height)
		{

		}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void onUpdate() = 0;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;

		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());

		virtual void* getNativeWindow() const = 0;
	};
}
