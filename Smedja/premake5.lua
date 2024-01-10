project "Smedja"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

    links {
	"glfw",
	"glad",
	"imgui",
    }

    pchheader "pch.h"

    files {
	"src/**.h",
	"src/**.cpp"
    }

    includedirs {
	"src",	-- easy access to the project root for includes
	"%{IncludeDir.spdlog}",
	"%{IncludeDir.glfw}",
	"%{IncludeDir.glad}",
	"%{IncludeDir.imgui}",
	"%{IncludeDir.glm}",
	"%{IncludeDir.stb_image}"
    }

    defines {
	"GLFW_INCLUDE_NONE"
    }

    filter "system:linux"
	links {
	    "GL",
	    "X11",
	    "Xrandr",
	    "Xi",
	    "Xinerama",
	    "Xxf86vm",
	    "Xcursor",
	    "Xrender"
	}

	pic "On"

	systemversion "latest"
	staticruntime "On"

	defines
	{
	    "__linux__"
	}

    filter "system:windows"
	links {
	    "opengl32.lib",
	}

	systemversion "latest"
	staticruntime "On"

	defines
	{
	    "_WIN64",
	    "_CRT_SECURE_NO_WARNINGS"
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

