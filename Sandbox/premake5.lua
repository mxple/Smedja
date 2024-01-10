project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    staticruntime "off"

    targetdir("../bin/" .. outputdir .. "/%{prj.name}")
    objdir("../obj/" .. outputdir .. "/%{prj.name}")

    links {
	"Smedja"
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

    filter "configurations:Debug"
	defines "DEBUG"
	runtime "Debug"
	symbols "on"

    filter "configurations:Release"
	defines "RELEASE"
	runtime "Release"
	optimize "on"
