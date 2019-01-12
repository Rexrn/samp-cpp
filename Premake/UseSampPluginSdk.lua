-- For Windows: links SampPluginSdk project.
-- For Linux: injects required samp-plugin-sdk code.
edge.useSampPluginSdk = function (sdkRoot)

	includedirs {
		sdkRoot,
		path.join(sdkRoot, "amx"),
	}

	if string.match(_ACTION, "vs%d%d%d%d") ~= nil then
		links { "SampPluginSdk" }
	else
		files { path.join(sdkRoot, "amxplugin.cpp") } 
	end

end

edge.useSampPluginSdkRemote = function (sdkRoot, edgeRoot)

	includedirs {
		sdkRoot,
		path.join(sdkRoot, "amx"),
	}

	if string.match(_ACTION, "vs%d%d%d%d") ~= nil then
		links { path.join(edgeRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}/SampPluginSdk") }
	else
		files { path.join(sdkRoot, "amxplugin.cpp") } 
	end

end