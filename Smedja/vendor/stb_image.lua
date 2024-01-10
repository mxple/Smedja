project "stb_image"
    kind "StaticLib"
    language "C++"

    targetdir "../../bin/%{cfg.buildcfg}"
    objdir "../../obj/%{cfg.buildcfg}"

    includedirs { "stb_image/" }

    files
    {
	"stb_image/include/**",
    }

    --  consider defining STB_IMAGE_IMPLEMENTATION here

    filter "system:linux"
	pic "On"

	systemversion "latest"
	staticruntime "On"

    filter "system:windows"
	systemversion "latest"
	staticruntime "On"

	defines
	{
	    "_STB_IMAGE_WIN32",
	    "_CRT_SECURE_NO_WARNINGS"
	}

    filter "configurations:Debug"
	runtime "Debug"
	symbols "on"

    filter "configurations:Release"
	runtime "Release"
	optimize "speed"
