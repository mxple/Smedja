project "glad"
    kind "StaticLib"
    language "C"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")
    
    includedirs { "glad/include/" }

    files 
    {
	"glad/src/glad.c",
	"glad/include/glad/glad.h",
	"glad/include/KHR/khrplatform.h"
    }

    filter "system:linux"
	pic "On"

	systemversion "latest"
	staticruntime "On"

	defines
	{
	    "_GLAD_X11"
	}

    filter "system:windows"
	systemversion "latest"
	staticruntime "On"

	defines 
	{ 
	    "_GLAD_WIN32",
	    "_CRT_SECURE_NO_WARNINGS"
	}

    filter "configurations:Debug"
	runtime "Debug"
	symbols "on"

    filter "configurations:Release"
	runtime "Release"
	optimize "speed"
