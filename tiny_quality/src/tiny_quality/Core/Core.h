#pragma once

#include <memory>

#ifdef TQ_PLATFORM_WINDOWS
#if TQ_DYNAMIC_LINK
	#ifdef TQ_BUILD_DLL
		#define TINY_QUALITY_API __declspec(dllexport)
	#else
		#define TINY_QUALITY_API __declspec(dllimport)
	#endif
#else
#define TINY_QUALITY_API
#endif
#else
	#error tiny_quality only support Windows!
#endif

#ifdef TQ_DEBUG
	#define TQ_ENABLE_ASSERTS
#endif

#ifdef TQ_ENABLE_ASSERTS
#define TQ_ASSERT(x, ...) { if(!(x)) { TQ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define TQ_CORE_ASSERT(x, ...) { if(!(x)) { TQ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define TQ_ASSERT(x, ...)
#define TQ_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1<<x)

#define TQ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace tiny_quality {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}
