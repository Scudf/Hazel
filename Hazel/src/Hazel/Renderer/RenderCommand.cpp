#include "hzpch.h"
#include "Hazel/Renderer/RenderCommand.h"

namespace Hazel
{
	Scope<RendererAPI> RenderCommand::m_rendererAPI = RendererAPI::Create();
}
