#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "tiny_quality/Core/Log.h"

#include "tiny_quality/Core/Debug/instrumentor.h"

#ifdef TQ_PLATFORM_WINDOWS
	#include <Windows.h>
#endif