-- premake5.lua
workspace "Teris"
    platforms {
        "x64"
    }
    --architecture = "x86_64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.platform}"

-- include directories
IncludeDir = {}
IncludeDir["GLFW"] = "teris/vendor/GLFW/include"
IncludeDir["Glad"] = "teris/vendor/Glad/include"
IncludeDir["ImGui"] = "teris/vendor/imgui"

include "teris/vendor/GLFW"
include "teris/vendor/Glad"
include "teris/vendor/ImGui";

project "Teris"
    location "teris"
    kind "SharedLib"
    language "C++"

    targetdir ("bin\\" .. outputdir .. "\\%{prj.name}")
    objdir ("bin-int\\" .. outputdir .. "\\%{prj.name}")

    pchheader "tpch.h"
    pchsource "src/tpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "TS_PLATFORM_WINDOWS",
            "TS_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("copy ..\\bin\\" .. outputdir .. "\\Teris\\Teris.dll " .. "..\\bin\\" .. outputdir .. "\\Sandbox\\")
        }

    filter "configurations:Debug"
        defines { "TS_DEBUG", "TS_ENABLE_ASSERTS" }
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "TS_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "TS_DIST"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "teris/src"
    }

    links
    {
        "Teris"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "TS_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "TS_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "TS_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "TS_DIST"
        buildoptions "/MD"
        optimize "On"