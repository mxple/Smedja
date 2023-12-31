workspace "Smedja"
	architecture "x64"

	configurations {
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Smedja/vendor/GLFW/include"
IncludeDir["glad"] = "Smedja/vendor/glad/include"
IncludeDir["ImGui"] = "Smedja/vendor/ImGui"

include "Smedja/vendor/GLFW"	-- include premake file
include "Smedja/vendor/glad"	-- include premake file
include "Smedja/vendor/ImGui"	-- include premake file

project "Smedja"
	location "Smedja"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	links {
		"GLFW",
		"glad",
		"ImGui",
		"X11",
		"Xrandr",
		"Xi",
		"Xinerama",
		"Xxf86vm",
		"Xcursor",
		"Xrender",
		"GL",
	}

	pchheader "pch.h"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
	}

	defines {
		"GLFW_INCLUDE_NONE"
	}

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	links {
		"GLFW",
		"glad",
		"ImGui",
		"X11",
		"Xrandr",
		"Xi",
		"Xinerama",
		"Xxf86vm",
		"Xcursor",
		"Xrender",
		"GL",
		"Smedja"
	}

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Smedja/src",
		"Smedja/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
	}

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "On"
