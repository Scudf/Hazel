#pragma once

#include <memory>

#define HAZEL_MEMORY_DISABLED_WARNINGS 6255 6386

#ifdef HZ_DYNAMIC_LINK
	#ifdef HZ_PLATFORM_WINDOWS
		#ifdef HZ_BUILD_DLL
			#define HAZEL_API __declspec(dllexport)
		#else
			#define HAZEL_API __declspec(dllimport)
		#endif
	#else
		#error Hazel only supports Windows!
	#endif
#else
	#define HAZEL_API
#endif

#ifdef HZ_DEBUG
	#define HZ_ENABLE_ASSERTS
#endif

#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hazel
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template <class _Ty, class... _Types>
	static Ref<_Ty> MakeRef(_Types&&... _Args)
	{
		return std::make_shared<_Ty>(std::forward<_Types>(_Args)...);
	}

	template <class _Ty, class... _Types>
	static Ref<_Ty> MakeScope(_Types&&... _Args)
	{
		return std::make_unique<_Ty>(std::forward<_Types>(_Args)...);
	}
}
