repoRoot = os.getcwd()

include ("BuildConfig.user.lua")

workspace "SAMPEDGEngine"
	location "Build"
	platforms { "x86", "x64" }
	configurations { "Debug", "Release" }

	if os.host() == "macosx" then
		removeplatforms { "x86" }
	end

	filter "platforms:*32"
		architecture "x86"

	filter "platforms:*64"
		architecture "x86_64"

	filter "configurations:Debug"
		defines { "DEBUG" }
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

	