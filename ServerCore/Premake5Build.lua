project "ServerCore"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	location (path.join(repoRoot, "Build/%{prj.name}"))
	targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}"))

	includedirs {
		path.join(userConfig.deps.quickmaffs.root, "include"),
		userConfig.deps.sampgdk.root,
		path.join(repoRoot, "Engine/Include")
	}

	files {
		"ServerCore.cpp"
	}