workspace "Smedja"
	architecture "x64"

	configurations {
		"Debug",
		"Release"
	}

    flags { "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glad"] = "Smedja/vendor/glad/include"
IncludeDir["glfw"] = "Smedja/vendor/glfw/include"
IncludeDir["imgui"] = "Smedja/vendor/imgui"
IncludeDir["glm"] = "Smedja/vendor/glm/glm"
IncludeDir["spdlog"] = "Smedja/vendor/spdlog/include"
IncludeDir["stb_image"] = "Smedja/vendor/stb_image"

include "Smedja/vendor/glad.lua"
include "Smedja/vendor/glfw.lua"
include "Smedja/vendor/glm.lua"
include "Smedja/vendor/imgui.lua"
include "Smedja/vendor/spdlog.lua"
include "Smedja/vendor/stb_image.lua"

project "Smedja"
	location "Smedja"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	links {
		"glfw",
		"glad",
		"imgui",
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
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
	}

	defines {
		"GLFW_INCLUDE_NONE"
	}

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
	}

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"
