project "glad"
	kind "StaticLib"
	language "C"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

	filter "system:linux"
		pic "On"
	--
	-- filter "configurations:Debug"
	-- 	runtime "Debug"
	-- 	symbols "on"
	--
	-- filter "configurations:Release"
	-- 	runtime "Release"
	-- 	optimize "speed"
