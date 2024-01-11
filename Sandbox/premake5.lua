project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    staticruntime "off"

    targetdir("../bin/" .. outputdir .. "/%{prj.name}")
    objdir("../obj/" .. outputdir .. "/%{prj.name}")

    -- premake does not seem to propagate links
    links {
	"Smedja",
    	"glfw",
	"glad",
	"imgui",
    }

    files {
	"src/**.h",
	"src/**.cpp"
    }

    includedirs {
	"%{wks.location}/Smedja/src",
	"%{IncludeDir.spdlog}",
	"%{IncludeDir.glfw}",
	"%{IncludeDir.glad}",
	"%{IncludeDir.imgui}",
	"%{IncludeDir.glm}",
	"%{IncludeDir.stb_image}"
    }

    filter "system:macosx"
	links 
	{
	    "Carbon.framework",
	    "Cocoa.framework",
	    "CoreVideo.framework",
	    "IOKit.framework",
	    "OpenGL.framework",
	}

    filter "configurations:Debug"
	defines "DEBUG"
	runtime "Debug"
	symbols "on"

    filter "configurations:Release"
	defines "RELEASE"
	runtime "Release"
	optimize "on"
