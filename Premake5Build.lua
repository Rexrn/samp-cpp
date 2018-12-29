repoRoot = os.getcwd()

include ("BuildConfig.lua")

-- Custom library:
include ("Premake/Library.lua")

workspace "SAMPEDGEngine"
	location "Build"
	platforms { "x86", "x64" }
	configurations { "Debug", "Release" }

	-- Mac OS X does not support x86 (??? - confirm this).
	if os.host() == "macosx" then
		removeplatforms { "x86" }
	end

	-- Linux specific configuration.
	if os.host() == "linux" then
		defines { "LINUX" }
	end

	-- MSBuild specific configuration
	if string.match(_ACTION, "vs%d%d%d%d") ~= nil then
		filter {"system:windows"}
    		systemversion(edge.getWindowsSDKVersion() .. ".0")
	end

	-- gmake specific configuration
	if _ACTION == "gmake" then
		links { "stdc++fs", "dl", "pthread" }
		buildoptions { "-fPIC" }
	end	
		

	-- Setup platforms:
	filter "platforms:*32"
		architecture "x86"

	filter "platforms:*64"
		architecture "x86_64"

	-- Setup configurations:
	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

	filter {}

	-- Projects:
	include ("Engine/Premake5Build.lua")
	include ("ServerCore/Premake5Build.lua")

	-- TODO: include other project files here

	-- Extensions:
	if userConfig.build.extensions then
		group "Extensions"
		include("Extensions/Premake5Build.lua")
	end
	
	-- Examples:
	if userConfig.build.examples then
		group "Examples"
		include("Examples/Premake5Build.lua")
	end

	-- UnitTests:
	if userConfig.build.unitTests then
		group "UnitTests"
		include("UnitTests/Premake5Build.lua")
	end

	-- ThirdParty:
	if userConfig.build.thirdParty then
		group "ThirdParty"
		include("ThirdParty/Premake5Build.lua")
	end

	