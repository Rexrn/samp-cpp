-- ===== SampPluginSdk Project =====
-- Built only for Visual Studio. It encapsulates samp-plugin-sdk source code.
-- Because of that you can link this library easily instead of adding remote source files.
-- TODO: Make this work also for Linux.

-- Build this project only if using Visual Studio.
if string.match(_ACTION, "vs%d%d%d%d") ~= nil then
	-- The SampPluginSdk project:
	project "SampPluginSdk"
		kind "StaticLib"

		location (path.join(repoRoot, "Build/%{prj.name}"))
		targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}"))

		includedirs {
			-- Samp Plugin Sdk root directory
			userConfig.deps.samp_plugin_sdk.root,
			-- Samp Plugin Sdk /amx directory
			path.join(userConfig.deps.samp_plugin_sdk.root, "amx"),
		}

		files {
			path.join(userConfig.deps.samp_plugin_sdk.root, "amxplugin.cpp"),
		}
end