#pragma once

namespace Hazel
{
	enum class ERendererAPI
	{
		NONE,
		OPEN_GL
	};

	class Renderer
	{
	private:
		static ERendererAPI s_rendererAPI;

	public:
		static ERendererAPI GetAPI() { return s_rendererAPI; }
	};
}
