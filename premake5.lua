workspace "Smedja"
    architecture "x64"

    configurations {
	"Debug",
	"Release"
    }

flags {"MultiProcessorCompile"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glad"] = "%{wks.location}/Smedja/vendor/glad/include"
IncludeDir["glfw"] = "%{wks.location}/Smedja/vendor/glfw/include"
IncludeDir["imgui"] = "%{wks.location}/Smedja/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Smedja/vendor/glm/glm"
IncludeDir["spdlog"] = "%{wks.location}/Smedja/vendor/spdlog/include"
IncludeDir["stb_image"] = "%{wks.location}/Smedja/vendor/stb_image"

include "Smedja/vendor/glad.lua"
include "Smedja/vendor/glfw.lua"
include "Smedja/vendor/glm.lua"
include "Smedja/vendor/imgui.lua"
include "Smedja/vendor/spdlog.lua"
include "Smedja/vendor/stb_image.lua"

include "Smedja"
include "Sandbox"
