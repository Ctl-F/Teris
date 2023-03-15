-- premake5.lua
workspace "Teris"
    architecture = "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-${cfg.architecture}"

project "Teris"
    location "teris"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    --includedirs
    --{
    --
    --}

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "10.0"

        defines 
        {
            "TS_PLATFORM_WINDOWS",
            "TS_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "TS_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "TS_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "TS_DEBUG"
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
        systemversion "10.0"

        defines 
        {
            "TS_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "TS_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "TS_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "TS_DEBUG"
        optimize "On"