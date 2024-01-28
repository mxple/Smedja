workspace "RectPackerTest"
    architecture "x64"
    language "C++"
    cppdialect "C++17"

    configurations {
        "Release"
    }

SmedjaDir = "../../Smedja/"

project "RectPackerTest"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files {
        SmedjaDir .. "src/vendor/stb_image/stb_image.h",
        -- SmedjaDir .. "src/Smedja/Graphics/RectPacker.h",
        "src/stb_write/**",
        "src/**"
    }

    includedirs {
        -- SmedjaDir .. "src/Smedja/Graphics",
        SmedjaDir .. "/vendor/stb_image",
        "src/stb_write"
    }

    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "on"
