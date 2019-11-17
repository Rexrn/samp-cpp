project "Ext_ResourceIO"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	location (path.join(repoRoot, "Build/Extensions/%{prj.name}"))
	targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}/Extensions"))

	edge.configurePCH(
			"include/SAMPCpp/Ext/ResourceIO/ResourceIOPCH.hpp",
			"src/ResourceIOPCH.cpp",
			"SAMPCPP_EXT_RESOURCEIO_PCH"
		)

	includedirs {
		"include",
		
		-- SAMPCpp:
		path.join(repoRoot, "Engine/include"),

		-- SAMPGDK:
		path.join(userConfig.deps.sampgdk.root, "include"),
		
		-- SAMP Plugin SDK:
		userConfig.deps.samp_plugin_sdk.root,
		path.join(userConfig.deps.samp_plugin_sdk.root, "amx"),
		
		-- QuickMaffs:
		path.join(userConfig.deps.quickmaffs.root, "include"),

		-- RapidXML:
		userConfig.deps.rapidxml.root
	}
	
	files {
		"include/SAMPCpp/Ext/**.hpp",
		"src/**.cpp"
	}
