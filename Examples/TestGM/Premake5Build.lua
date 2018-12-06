project "TestGM"
	kind "SharedLib"
	language "C++"
	location (path.join(repoRoot, "Build/%{prj.name}"))
	targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}"))

	includedirs {
		path.join(deps.quickmaffs.root, "include"),
		deps.sampgdk.root
		path.join(repoRoot, "Engine/Include")
	}

	links {
		"Engine"
	}

	files {
		"Main.cpp"
	}