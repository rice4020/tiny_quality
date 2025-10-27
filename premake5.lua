workspace "tiny_quality"
	architecture "x64"
	startproject "Sandbox"

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
IncludeDir["glm"] = "tiny_quality/vendor/glm"
IncludeDir["stb_image"] = "tiny_quality/vendor/stb_image"

include "tiny_quality/vendor/GLFW"
include "tiny_quality/vendor/Glad"
include "tiny_quality/vendor/imgui"

project "tiny_quality"
	location "tiny_quality"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"	
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "tqpch.h"
	pchsource "tiny_quality/src/tqpch.cpp"

	files{ 
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

    defines {
        "_CRT_SECURE_NO_WARNINGS"
	}

	includedirs { 
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}
	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines { 
			"TQ_PLATFORM_WINDOWS",
			"TQ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "TQ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TQ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "TQ_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp"
	}
	includedirs { 
		"tiny_quality/vendor/spdlog/include", 
		"tiny_quality/src", 
		"tiny_quality/vendor",
		"%{IncludeDir.glm}"
	}
	links{
		"tiny_quality"
	}

	filter "system:windows"
		systemversion "latest"

		defines { "TQ_PLATFORM_WINDOWS"	}
	
	filter "configurations:Debug"
		defines "TQ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TQ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "TQ_DIST"
		runtime "Release"		
		optimize "on"