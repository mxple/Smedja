project "imgui"
    kind "StaticLib"
    language "C++"

    targetdir ("../../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../../obj/" .. outputdir .. "/%{prj.name}")

    files
    {
	"imgui/imconfig.h",
	"imgui/imgui.h",
	"imgui/imgui.cpp",
	"imgui/imgui_draw.cpp",
	"imgui/imgui_internal.h",
	"imgui/imgui_tables.cpp",
	"imgui/imgui_widgets.cpp",
	"imgui/imgui_rectpack.h",
	"imgui/imgui_textedit.h",
	"imgui/imgui_truetype.h",
	"imgui/imgui_demo.cpp",   -- recommended to leave in to show demo window
	"imgui/backends/imgui_impl_opengl3.h",
	"imgui/backends/imgui_impl_opengl3.cpp",
    }

    includedirs {
	"imgui/"
    }

    defines 
    {
	"IMGUI_IMPL_OPENGL_LOADER_GLAD"
    }

    filter "system:linux"
	pic "On"

	systemversion "latest"
	staticruntime "on"

	defines
	{
	    "_IMGUI_X11"
	}

    filter "system:windows"
	systemversion "latest"
	staticruntime "on"

	defines
	{
	    "_IMGUI_WIN32",
	    "_CRT_SECURE_NO_WARNINGS"
	}

    filter "configurations:Debug"
    	runtime "Debug"
    	symbols "on"

    filter "configurations:Release"
    	runtime "Release"
    	optimize "speed"
