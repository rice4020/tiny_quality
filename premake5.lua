workspace "tiny_quality"
	architecture "x64"

	configurations { 
		"Debug",
		"Release",
		"Dist" 
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "tiny_quality/vendor/GLFW/include"
IncludeDir["Glad"] = "tiny_quality/vendor/Glad/include"
IncludeDir["ImGui"] = "tiny_quality/vendor/imgui"

include "tiny_quality/vendor/GLFW"
include "tiny_quality/vendor/Glad"
include "tiny_quality/vendor/imgui"

project "tiny_quality"
	location "tiny_quality"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "tqpch.h"
	pchsource "tiny_quality/src/tqpch.cpp"

	files{ 
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs { 
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}
	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines { 
			"TQ_PLATFORM_WINDOWS",
			"TQ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox") }
	
	filter "configurations:Debug"
		defines "TQ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TQ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "TQ_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp"
	}
	includedirs { 
		"tiny_quality/vendor/spdlog/include", 
		"tiny_quality/src" 
	}
	links{
		"tiny_quality"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines { "TQ_PLATFORM_WINDOWS"	}
	
	filter "configurations:Debug"
		defines "TQ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TQ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "TQ_DIST"
		runtime "Release"		
		optimize "On"