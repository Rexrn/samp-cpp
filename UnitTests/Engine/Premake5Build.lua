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
		path.join(repoRoot, "Dependencies/sampgdk"),

		-- QuickMaffs
		path.join(userConfig.deps.quickmaffs.root, "include"),

		-- Google Test
		path.join(userConfig.deps.gtest.root, "googletest/include")
	}

	links {
		"Engine"
	}

	-- Link Google Test

	filter "configurations:Debug"
		links {
			path.join(userConfig.deps.gtest.root, "lib/Debug/gtestd"),
			path.join(userConfig.deps.gtest.root, "lib/Debug/gtest_maind")
		}
		

	filter "configurations:Release"
		links {
			path.join(userConfig.deps.gtest.root, "lib/Release/gtest"),
			path.join(userConfig.deps.gtest.root, "lib/Release/gtest_main")
		}

	filter {}

	if string.match(_ACTION, "gmake(2)?") ~= nil then
		links { "stdc++fs" }
	end	

	files {
		"src/**.hpp",
		"src/**.cpp"
	}