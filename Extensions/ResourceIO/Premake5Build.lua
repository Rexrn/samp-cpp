project "Ext_ResourceIO"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	location (path.join(repoRoot, "Build/%{prj.name}"))
	targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}"))

	includedirs {
		path.join(userConfig.deps.quickmaffs.root, "include"),
		userConfig.deps.rapidxml.root,
		userConfig.deps.sampgdk.root,
		path.join(repoRoot, "Engine/Include"),
		"include"
	}

	files {
		"include/SAMP-EDGEngine/Ext/ResourceIO/Dependencies/RapidXML.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/Deserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/Everything.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/MapObjectDeserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/MapObjectMaterialDeserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/MapObjectMaterialSerializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/MapObjectSerializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/PAWNDeserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/PAWNSceneDeserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/RemovedBuildingDeserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/RemovedBuildingSerializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/SceneDeserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/SceneSerializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/Serializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLDeserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLGlobalObjectDeserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLGlobalObjectSerializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLHelperFunctions.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLMapObjectDeserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLMapObjectMaterialDeserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLMapObjectMaterialSerializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLMapObjectSerializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLNames.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLPerPlayerObjectDeserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLPerPlayerObjectSerializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLRemovedBuildingDeserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLRemovedBuildingSerializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLSceneDeserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLSceneSerializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLSerializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLTextMaterialDeserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLTextMaterialSerializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLTextureMaterialDeserializer.hpp",
		"include/SAMP-EDGEngine/Ext/ResourceIO/XMLTextureMaterialSerializer.hpp",

		"src/PAWNSceneDeserializer.cpp",
		"src/XMLGlobalObjectDeserializer.cpp",
		"src/XMLGlobalObjectSerializer.cpp",
		"src/XMLHelperFunctions.cpp",
		"src/XMLMapObjectDeserializer.cpp",
		"src/XMLMapObjectMaterialDeserializer.cpp",
		"src/XMLMapObjectSerializer.cpp",
		"src/XMLPerPlayerObjectDeserializer.cpp",
		"src/XMLPerPlayerObjectSerializer.cpp",
		"src/XMLRemovedBuildingDeserializer.cpp",
		"src/XMLRemovedBuildingSerializer.cpp",
		"src/XMLSceneDeserializer.cpp",
		"src/XMLSceneSerializer.cpp",
		"src/XMLTextMaterialDeserializer.cpp",
		"src/XMLTextMaterialSerializer.cpp",
		"src/XMLTextureMaterialDeserializer.cpp",
		"src/XMLTextureMaterialSerializer.cpp"
	}
