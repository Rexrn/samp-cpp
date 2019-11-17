if userConfig.build.examples and not userConfig.build.extensions then
	printf("TestGM example requires to build extensions. Skipping...")
else
	project "TestGM"
		kind "SharedLib"
		language "C++"
		cppdialect "C++17"
		location (path.join(repoRoot, "Build/Examples/%{prj.name}"))
		targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}/Examples"))

		-- Use .def file with Visual Studio compiler.
		if string.match(_ACTION, "vs%d%d%d%d") ~= nil then
			linkoptions { "/DEF:\"" .. path.join(repoRoot, "SymbolsExportList.def") .. "\""}
		end

		includedirs {
			-- Ext_ResourceIO:
			path.join(repoRoot, "Extensions/ResourceIO/include"),

			-- SAMPCpp:
			path.join(repoRoot, "Engine/include"),

			-- SAMPGDK:
			path.join(userConfig.deps.sampgdk.root, "include"),
			
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

		edge.useSampPluginSdk(userConfig.deps.samp_plugin_sdk.root)

		files {
			"src/Main.cpp",
		}
end