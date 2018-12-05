repoRoot = os.getcwd()

printf("Repo root: %s", repoRoot)

workspace "SAMPEDGEngine"
	location "build"
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

	-- TODO: include other project files here


	