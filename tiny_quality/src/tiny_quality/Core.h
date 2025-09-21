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
