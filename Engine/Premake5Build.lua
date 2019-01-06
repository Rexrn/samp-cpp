project "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	location (path.join(repoRoot, "Build/%{prj.name}"))
	targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}"))

	edge.configurePCH(
			"include/SAMP-EDGEngine/EnginePCH.hpp",
			"src/EnginePCH.cpp",
			"SAMPEDGENGINE_PCH"
		)
		
	includedirs {
		"include",

		-- SAMPGDK
		path.join(userConfig.deps.sampgdk.root, "include"),

		-- SAMP Plugin SDK
		userConfig.deps.samp_plugin_sdk.root,
		path.join(userConfig.deps.samp_plugin_sdk.root, "amx"),

		-- QuickMaffs
		path.join(userConfig.deps.quickmaffs.root, "include")
	}

	files {
		-- C++ files
		"include/SAMP-EDGEngine/**.hpp",
		"include/SAMP-EDGEngine/**.inl",
		"src/**.cpp"
	}
		

