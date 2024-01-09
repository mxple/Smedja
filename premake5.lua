workspace "Smedja"
	architecture "x64"

	configurations {
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glfw"] = "Smedja/vendor/glfw/include"
IncludeDir["glad"] = "Smedja/vendor/glad/include"
IncludeDir["ImGui"] = "Smedja/vendor/ImGui"
IncludeDir["glm"] = "Smedja/vendor/glm/glm"
IncludeDir["spdlog"] = "Smedja/vendor/spdlog/include"
IncludeDir["stb_image"] = "Smedja/vendor/stb_image"

include "Smedja/vendor/glfw"	-- include premake file
include "Smedja/vendor/glad"	-- include premake file
include "Smedja/vendor/ImGui"	-- include premake file

project "Smedja"
	location "Smedja"
	kind "sharedlib"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	links {
		"glfw",
		"glad",
		"ImGui",
		"GL",
		"X11",
		"Xrandr",
		"Xi",
		"Xinerama",
		"Xxf86vm",
		"Xcursor",
		"Xrender",
	}

	pchheader "pch.h"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
	}

	defines {
		"GLFW_INCLUDE_NONE"
	}

	-- Enable SSE2 vector processing
	vectorextensions "SSE2"

	filter "configurations:Debug"
		-- warnings "Extra"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"
		-- optimize "on" -- hack to use stb_image with SIMD enabled

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	links {
		"Smedja"
	}

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Smedja/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
	}

	-- Enable SSE2 vector processing
	vectorextensions "SSE2"

	filter "configurations:Debug"
		-- warnings "Extra"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"
