project "Ext_ResourceIO"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	location (path.join(repoRoot, "Build/Extensions/%{prj.name}"))
	targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}/Extensions"))

	edge.configurePCH(
			"include/SAMP-EDGEngine/Ext/ResourceIO/ResourceIOPCH.hpp",
			"src/ResourceIOPCH.cpp",
			"SAMPEDGENGINE_EXT_RESOURCEIO_PCH"
		)

	includedirs {
		"include",
		path.join(userConfig.deps.quickmaffs.root, "include"),
		userConfig.deps.rapidxml.root,
		path.join(userConfig.deps.sampgdk.root, "include"),
		path.join(repoRoot, "Engine/include")
	}

	files {
		"include/SAMP-EDGEngine/Ext/**.hpp",
		"src/**.cpp"
	}
