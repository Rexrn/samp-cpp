if userConfig.build.examples and not userConfig.build.extensions then
	printf("TestGM example requires to build extensions. Skipping...")
else
	project "TestGM"
		kind "SharedLib"
		language "C++"
		cppdialect "C++17"
		location (path.join(repoRoot, "Build/%{prj.name}"))
		targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}"))

		includedirs {
			path.join(deps.quickmaffs.root, "include"),
			deps.sampgdk.root
			path.join(repoRoot, "Engine/Include")
		}

		links {
			"Engine",
			"Ext::ResourceIO"
		}

		files {
			"Main.cpp"
		}
end