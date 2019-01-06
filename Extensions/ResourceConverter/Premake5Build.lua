project "Ext_ResourceConverter"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	location (path.join(repoRoot, "Build/Extensions/%{prj.name}"))
	targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}/Extensions"))

	includedirs {
		-- Ext_ResourceIO:
		path.join(repoRoot, "Extensions/ResourceIO/include"),

		-- SAMP-EDGEngine:
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

	-- gmake adds ServerCore.cpp directly (TODO: change this.)
	if _ACTION == "gmake" then
		files { path.join(repoRoot, "ServerCore/src/ServerCore.cpp") }
		links {
			"Ext_ResourceIO",
			"Engine",
			-- SAMPGDK:
			path.join(userConfig.deps.sampgdk.root, "lib/%{cfg.platform}/%{cfg.buildcfg}/sampgdk")
		}
		buildoptions { "-Wno-attributes" }
	else
		links {
			"Ext_ResourceIO",
			"ServerCore",
			"Engine",
			-- SAMPGDK:
			path.join(userConfig.deps.sampgdk.root, "lib/%{cfg.platform}/%{cfg.buildcfg}/sampgdk")
		}
	end

	-- gmake (Linux) specific configuration
	if os.host() == "linux" and _ACTION == "gmake" then
		links { "dl" }
	end	

	files {
		"src/Main.cpp"
	}