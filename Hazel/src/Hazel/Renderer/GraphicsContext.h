#pragma once

namespace Hazel
{
	class GraphicsContext
	{
	public:
		static Scope<GraphicsContext> Create(void* window);

		virtual void init() = 0;
		virtual void swapBuffers() = 0;
	};
}
