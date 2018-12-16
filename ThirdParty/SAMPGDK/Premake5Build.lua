project "SAMPGDK"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	location (path.join(repoRoot, "Build/ThirdParty/%{prj.name}"))
	targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}/ThirdParty"))

	includedirs {
		"include"
	}

	files {
		"include/SAMPGDK/**.h",
		"include/SAMPGDK/**.hpp",
		"src/**.c",
		"src/**.cpp"
	}
		

	filter "files:**.c"
		compileas "C"