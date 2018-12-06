if userConfig.build.examples and not userConfig.build.extensions then
	printf("TestGM example requires to build extensions. Skipping...")
else
	project "TestGM"
		kind "SharedLib"
		language "C++"
		cppdialect "C++17"
		location (path.join(repoRoot, "Build/Examples/%{prj.name}"))
		targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}/Examples"))

		includedirs {
			path.join(userConfig.deps.quickmaffs.root, "include"),
			userConfig.deps.rapidxml.root,
			userConfig.deps.sampgdk.root,
			path.join(repoRoot, "Engine/include"),
			path.join(repoRoot, "Extensions/ResourceIO/include")
		}

		links {
			"Ext_ResourceIO",
			"ServerCore",
			"Engine"
		}

		files {
			"Main.cpp"
		}

		if string.match(_ACTION, "vs%d%d%d%d") ~= nil then
			linkoptions { "/DEF:\"" .. path.join(repoRoot, "SymbolsExportList.def") .. "\""}
		elseif string.match(_ACTION, "gmake(2)?") ~= nil then
			links { "stdc++fs" }
		end
end