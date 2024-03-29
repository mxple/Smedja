project "spdlog"
    kind "Makefile"
    language "C++"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

    includedirs { "spdlog/include/" }

    files
    {
	"spdlog/include/**",
    }

    filter "system:linux"
	pic "On"

	systemversion "latest"
	staticruntime "On"

	defines
	{
	    "_SPDLOG_X11"
	}

    filter "system:windows"
	systemversion "latest"
	staticruntime "On"

	defines
	{
	    "_SPDLOG_WIN32",
	    "_CRT_SECURE_NO_WARNINGS"
	}

    filter "configurations:Debug"
	runtime "Debug"
	symbols "on"

    filter "configurations:Release"
	runtime "Release"
	optimize "speed"
