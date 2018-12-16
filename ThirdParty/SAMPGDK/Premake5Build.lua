project "SAMPGDK"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	location (path.join(repoRoot, "Build/ThirdParty/%{prj.name}"))
	targetdir (path.join(repoRoot, "Bin/ThirdParty/%{cfg.platform}/%{cfg.buildcfg}"))

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