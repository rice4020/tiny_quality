#pragma once


#ifdef TQ_PLATFORM_WINDOWS
	#ifdef TQ_BUILD_DLL
		#define TINY_QUALITY_API __declspec(dllexport)
	#else
		#define TINY_QUALITY_API __declspec(dllimport)
	#endif
#else
	#error tiny_quality only support Windows!
#endif

#ifdef TQ_ENABLE_ASSERTS
#define TQ_ASSERT(x, ...) { if(!(x)) { TQ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define TQ_CORE_ASSERT(x, ...) { if(!(x)) { TQ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define TQ_ASSERT(x, ...)
#define TQ_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1<<x)