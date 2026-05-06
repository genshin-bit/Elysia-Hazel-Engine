workspace "Hazel"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- 引擎项目：匹配你的项目名+文件夹结构
project "Elysia-Hazlel-Engine"
	location "Hazel" 
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"

	-- 【新增】强制使用 UTF-8 编码，解决 spdlog 编译错误
	buildoptions { "/utf-8" }

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

	-- 正确匹配：你的代码在Hazel/src文件夹下
	files
	{
		"Hazel/src/**.h",
		"Hazel/src/**.cpp",
	}

	-- 核心修正：加入src目录，让#include "Hazel/Application.h"能被正确解析
	includedirs
	{
		"Hazel/src",
		"Hazel/vendor/spdlog/include"
	}

	-- Windows平台专属配置
	filter "system:windows"
		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL" 
		}

		-- 编译后自动把DLL复制到Sandbox目录，方便调试
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")
		}

	-- 配置项
	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "On"

-- Sandbox测试项目：完全匹配你的文件夹结构
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"

	-- 【新增】强制使用 UTF-8 编码，解决 spdlog 编译错误
	buildoptions { "/utf-8" }

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

	-- 匹配你的Sandbox文件结构
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	-- 修正：加入引擎的src目录，Sandbox才能引用Hazel的头文件
	includedirs
	{
		"Hazel/src",
		"Hazel/vendor/spdlog/include"
	}

	-- 修正：链接正确的引擎项目名，和上面的project名完全一致
	links
	{
		"Elysia-Hazlel-Engine"
	}

	-- Windows平台专属配置
	filter "system:windows"
		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_DLL" 
		}

	-- 配置项
	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "On"