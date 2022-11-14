#include "hzpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel
{
	Scope<RendererAPI> RenderCommand::m_rendererAPI = MakeScope<OpenGLRendererAPI>();
}
