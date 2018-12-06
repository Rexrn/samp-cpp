project "Ext_ResourceConverter"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	location (path.join(repoRoot, "Build/Extensions/%{prj.name}"))
	targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}/Extensions"))

	includedirs {
		path.join(userConfig.deps.quickmaffs.root, "include"),
		userConfig.deps.rapidxml.root,
		userConfig.deps.sampgdk.root,
		path.join(repoRoot, "Engine/include"),
		path.join(repoRoot, "Extensions/ResourceIO/include")
	}

	links {
		"Engine",
		"Ext_ResourceIO"
	}

	files {
		"src/Main.cpp"
	}