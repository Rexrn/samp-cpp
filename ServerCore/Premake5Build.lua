project "ServerCore"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	location (path.join(repoRoot, "Build/%{prj.name}"))
	targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}"))

	includedirs {
		-- SAMPCpp
		path.join(repoRoot, "Engine/include"),

		-- SAMPGDK
		path.join(userConfig.deps.sampgdk.root, "include"),
		
		-- SAMP Plugin SDK
		userConfig.deps.samp_plugin_sdk.root,
		path.join(userConfig.deps.samp_plugin_sdk.root, "amx"),
		
		-- QuickMaffs
		path.join(userConfig.deps.quickmaffs.root, "include")
	}
	
	files {
		"src/ServerCore.cpp"
	}