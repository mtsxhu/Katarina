workspace "Katarina"
	architecture "x64"

	configurations 
	{ 
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Katarina"
	location "Katarina"
	kind "SharedLib"
	language "C++" 

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/HeaderFiles/**.h",
		"%{prj.name}/SourceFiles/**.cpp",
	}
	includedirs
	{
		"%{prj.name}/HeaderFiles",
		"%{prj.name}/vendor/spdlog/include"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17763.0"
		defines
		{
			"KT_PLATFORM_WINDWOS",
			"KT_BUILD_DLL"
		}

		postbuildcommands
		{
			("{copy} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "KT_DEBUG"
		symbols "On"
	
	filter "configurations:Realse"
		defines "KT_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "KT_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++" 
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/HeaderFiles/**.h",
		"%{prj.name}/SourceFiles/**.cpp"
	}
	includedirs
	{
		"Katarina/HeaderFiles",
		"Katarina/vendor/spdlog/include"
	}
	links
	{
		"Katarina"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17763.0"
		defines
		{
			"KT_PLATFORM_WINDWOS"
		}

	filter "configurations:Debug"
		defines "KT_DEBUG"
		symbols "On"
	
	filter "configurations:Realse"
		defines "KT_Realse"
		optimize "On"
	filter "configurations:Dist"
		defines "KT_DIST"
		optimize "On"