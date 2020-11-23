outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "Spike Engine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release"
	}

	project "Spike Engine"
		location "Spike Engine"
		kind "StaticLib"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("obj/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Dependencies/SDL2/include",
			"%{prj.name}/src"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			-- postbuildcommands
			-- {
			-- 	
			-- }

		filter "configurations:Debug"
			defines "SPIKE_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "SPIKE_RELEASE"
			optimize "On"

-----------------------------------------------------------------------

	project "Conway s Game of Life"
		location "Conway s Game of Life"
		kind "ConsoleApp"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("obj/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Dependencies/SDL2/include",
			"%{wks.name}/src"
		}

		libdirs
		{
			"bin/" .. outputdir .. "/Spike Engine",
			"Dependencies/SDL2/lib/x64/%{cfg.buildcfg}"
		}

		links
		{
			"SDL2",
			"SDL2main",
			"SDL2_ttf",
			"SDL2_image",
			"SDL2_mixer",
			"box2d",
			"Spike Engine"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines
			{
				"_CONSOLE"
			}

		filter "configurations:Debug"
			defines "_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "NDEBUG"
			optimize "On"

-----------------------------------------------------------------------

	project "Tetris"
		location "Tetris"
		kind "ConsoleApp"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("obj/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Dependencies/SDL2/include",
			"%{wks.name}/src"
		}

		libdirs
		{
			"bin/" .. outputdir .. "/Spike Engine",
			"Dependencies/SDL2/lib/x64/%{cfg.buildcfg}"
		}

		links
		{
			"SDL2",
			"SDL2main",
			"SDL2_ttf",
			"SDL2_image",
			"SDL2_mixer",
			"box2d",
			"Spike Engine"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines
			{
				"_CONSOLE"
			}

		filter "configurations:Debug"
			defines "_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "NDEBUG"
			optimize "On"