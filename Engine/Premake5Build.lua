-- BuildConfig contains dependency settings
include ("../BuildConfig.lua")

project "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	location (path.join(repoRoot, "Build/%{prj.name}"))
	targetdir (path.join(repoRoot, "Bin/%{cfg.platform}/%{cfg.buildcfg}"))

	includedirs {
		path.join(deps.quickmaffs.root, "include"),
		deps.sampgdk.root,
		"Include"
	}

	files {
		-- SAMPGDK files
		path.join(deps.sampgdk.root, "sampgdk.c"),
		path.join(deps.sampgdk.root, "amxplugin.cpp"),

		-- C++ files
		"EnginePCH.hpp",
		"Include/SAMP-EDGEngine/Everything.hpp",
		"Include/SAMP-EDGEngine/Core/Actions.hpp",
		"Include/SAMP-EDGEngine/Core/BasicInterfacesInc.hpp",
		"Include/SAMP-EDGEngine/Core/Clock.hpp",
		"Include/SAMP-EDGEngine/Core/Color.hpp",
		"Include/SAMP-EDGEngine/Core/ContainerInc.hpp",
		"Include/SAMP-EDGEngine/Core/Events.hpp",
		"Include/SAMP-EDGEngine/Core/Exceptions.hpp",
		"Include/SAMP-EDGEngine/Core/Placement.hpp",
		"Include/SAMP-EDGEngine/Core/Pointers.hpp",
		"Include/SAMP-EDGEngine/Core/TextInc.hpp",
		"Include/SAMP-EDGEngine/Core/TypesAndDefinitions.hpp",
		"Include/SAMP-EDGEngine/Core/TypeTraits.hpp",
		"Include/SAMP-EDGEngine/Core/BasicInterfaces/NonCopyable.hpp",
		"Include/SAMP-EDGEngine/Core/BasicInterfaces/PlacementTracker.hpp",
		"Include/SAMP-EDGEngine/Core/BasicInterfaces/Streamer.hpp",
		"Include/SAMP-EDGEngine/Core/BasicInterfaces/Updatable.hpp",
		"Include/SAMP-EDGEngine/Core/Container/DivisibleGrid2.hpp",
		"Include/SAMP-EDGEngine/Core/Container/DivisibleGrid3.hpp",
		"Include/SAMP-EDGEngine/Core/Text/ASCII.hpp",
		"Include/SAMP-EDGEngine/Core/Text/Essentials.hpp",
		"Include/SAMP-EDGEngine/Core/Text/StreamAlgorithm.hpp",
		"Include/SAMP-EDGEngine/Core/Text/StreamLoader.hpp",
		"Include/SAMP-EDGEngine/Core/Text/TokenIterator.hpp",
		"Include/SAMP-EDGEngine/Dependencies/QuickMaffs.hpp",
		"Include/SAMP-EDGEngine/Dependencies/SampGDK.hpp",
		"Include/SAMP-EDGEngine/Server/Chat.hpp",
		"Include/SAMP-EDGEngine/Server/Command.hpp",
		"Include/SAMP-EDGEngine/Server/CommandManager.hpp",
		"Include/SAMP-EDGEngine/Server/Dialog.hpp",
		"Include/SAMP-EDGEngine/Server/GameMode.hpp",
		"Include/SAMP-EDGEngine/Server/GlobalTextDraw.hpp",
		"Include/SAMP-EDGEngine/Server/GlobalTextDrawPanel.hpp",
		"Include/SAMP-EDGEngine/Server/Keyboard.hpp",
		"Include/SAMP-EDGEngine/Server/Player.hpp",
		"Include/SAMP-EDGEngine/Server/PlayerPool.hpp",
		"Include/SAMP-EDGEngine/Server/PlayerTextDraw.hpp",
		"Include/SAMP-EDGEngine/Server/PlayerTextDrawPanel.hpp",
		"Include/SAMP-EDGEngine/Server/Server.hpp",
		"Include/SAMP-EDGEngine/Server/Teleport.hpp",
		"Include/SAMP-EDGEngine/Server/TextDraw.hpp",
		"Include/SAMP-EDGEngine/Server/TextDrawOwner.hpp",
		"Include/SAMP-EDGEngine/Server/Weapon.hpp",
		"Include/SAMP-EDGEngine/World/3DNode.hpp",
		"Include/SAMP-EDGEngine/World/Checkpoint.hpp",
		"Include/SAMP-EDGEngine/World/GangZone.hpp",
		"Include/SAMP-EDGEngine/World/GlobalObject.hpp",
		"Include/SAMP-EDGEngine/World/Map.hpp",
		"Include/SAMP-EDGEngine/World/MapObject.hpp",
		"Include/SAMP-EDGEngine/World/PerPlayerObject.hpp",
		"Include/SAMP-EDGEngine/World/PersonalObject.hpp",
		"Include/SAMP-EDGEngine/World/Pickup.hpp",
		"Include/SAMP-EDGEngine/World/RaceCheckpoint.hpp",
		"Include/SAMP-EDGEngine/World/RemovedBuilding.hpp",
		"Include/SAMP-EDGEngine/World/Scene.hpp",
		"Include/SAMP-EDGEngine/World/UniversalObject.hpp",
		"Include/SAMP-EDGEngine/World/Vehicle.hpp",
		"Include/SAMP-EDGEngine/World/WI3DNode.hpp",
		"Include/SAMP-EDGEngine/World/WI3DStreamableNode.hpp",
		"Include/SAMP-EDGEngine/World/Streamer/CheckpointWrapper.hpp",
		"Include/SAMP-EDGEngine/World/Streamer/Chunk.hpp",
		"Include/SAMP-EDGEngine/World/Streamer/ChunkActor.hpp",
		"Include/SAMP-EDGEngine/World/Streamer/GlobalActorWrapper.hpp",
		"Include/SAMP-EDGEngine/World/Streamer/GlobalObjectWrapper.hpp",
		"Include/SAMP-EDGEngine/World/Streamer/PersonalObjectWrapper.hpp",
		"Include/SAMP-EDGEngine/World/Streamer/PlayerWrapper.hpp",
		"Include/SAMP-EDGEngine/World/Streamer/RaceCheckpointWrapper.hpp",
		"Include/SAMP-EDGEngine/World/Streamer/Streamer.hpp",
		"Include/SAMP-EDGEngine/World/Streamer/StreamerSettings.hpp",
		"Include/SAMP-EDGEngine/World/Streamer/UniversalObjectWrapper.hpp",
		"Include/SAMP-EDGEngine/World/Streamer/VehicleWrapper.hpp",

		"EnginePCH.cpp",
		"Source/Core/Actions.cpp",
		"Source/Core/Clock.cpp",
		"Source/Core/Color.cpp",
		"Source/Core/BasicInterfaces/PlacementTracker.cpp",
		"Source/Core/Text/ASCII.cpp",
		"Source/Server/Chat.cpp",
		"Source/Server/Command.cpp",
		"Source/Server/CommandManager.cpp",
		"Source/Server/Dialog.cpp",
		"Source/Server/GameMode.cpp",
		"Source/Server/GlobalTextDraw.cpp",
		"Source/Server/GlobalTextDrawPanel.cpp",
		"Source/Server/Keyboard.cpp",
		"Source/Server/Player.cpp",
		"Source/Server/PlayerPool.cpp",
		"Source/Server/PlayerTextDraw.cpp",
		"Source/Server/PlayerTextDrawPanel.cpp",
		"Source/Server/Server.cpp",
		"Source/Server/TextDraw.cpp",
		"Source/Server/TextDrawOwner.cpp",
		"Source/Server/Weapon.cpp",
		"Source/World/3DNode.cpp",
		"Source/World/Checkpoint.cpp",
		"Source/World/GangZone.cpp",
		"Source/World/GlobalObject.cpp",
		"Source/World/Map.cpp",
		"Source/World/MapObject.cpp",
		"Source/World/PerPlayerObject.cpp",
		"Source/World/PersonalObject.cpp",
		"Source/World/RaceCheckpoint.cpp",
		"Source/World/Scene.cpp",
		"Source/World/UniversalObject.cpp",
		"Source/World/Vehicle.cpp",
		"Source/World/WI3DNode.cpp",
		"Source/World/WI3DStreamableNode.cpp",
		"Source/World/Streamer/CheckpointWrapper.cpp",
		"Source/World/Streamer/Chunk.cpp",
		"Source/World/Streamer/ChunkActor.cpp",
		"Source/World/Streamer/GlobalActorWrapper.cpp",
		"Source/World/Streamer/GlobalObjectWrapper.cpp",
		"Source/World/Streamer/PersonalObjectWrapper.cpp",
		"Source/World/Streamer/PlayerWrapper.cpp",
		"Source/World/Streamer/Streamer.cpp",
		"Source/World/Streamer/UniversalObjectWrapper.cpp",
		"Source/World/Streamer/VehicleWrapper.cpp",
	}
