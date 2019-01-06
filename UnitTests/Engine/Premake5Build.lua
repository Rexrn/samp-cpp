project "UnitTest_Engine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	filename "Engine"

	location (path.join(repoRoot, "Build/%{prj.name}"))
	targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}/UnitTests"))

	includedirs {
		-- Engine
		path.join(repoRoot, "Engine/include"),

		-- SAMPGDK
		path.join(userConfig.deps.sampgdk.root, "include"),
		
		-- SAMP Plugin SDK
		userConfig.deps.samp_plugin_sdk.root,
		path.join(userConfig.deps.samp_plugin_sdk.root, "amx"),

		-- QuickMaffs
		path.join(userConfig.deps.quickmaffs.root, "include"),

		-- Google Test
		path.join(userConfig.deps.gtest.root, "include")
	}

	-- Link libraries:
	links {
		"Engine",
		path.join(userConfig.deps.sampgdk.root, "lib/%{cfg.platform}/%{cfg.buildcfg}/sampgdk"),
	}

	-- Link Google Test

	filter "configurations:Debug"
		links {
			path.join(userConfig.deps.gtest.root, "lib/%{cfg.platform}/%{cfg.buildcfg}/gtestd"),
			path.join(userConfig.deps.gtest.root, "lib/%{cfg.platform}/%{cfg.buildcfg}/gtest_maind")
		}
		

	filter "configurations:Release"
		links {
			path.join(userConfig.deps.gtest.root, "lib/%{cfg.platform}/%{cfg.buildcfg}/gtest"),
			path.join(userConfig.deps.gtest.root, "lib/%{cfg.platform}/%{cfg.buildcfg}/gtest_main")
		}

	filter {}

	files {
		"src/**.hpp",
		"src/**.cpp",
	}