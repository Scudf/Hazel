#include "hzpch.h"
#include "Hazel/Core/Input.h"

#ifdef HZ_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace Hazel
{
	Scope<Input> Input::s_instance = Create();

	Scope<Input> Input::Create()
	{
#ifdef HZ_PLATFORM_WINDOWS
		return MakeScope<WindowsInput>();
#else
		HZ_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}
