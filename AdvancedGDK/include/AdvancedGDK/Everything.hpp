// File description:
// Includes the whole ADVANCEDGDK library.

#pragma once

#ifndef ADVANCEDGDK_PCH
#define ADVANCEDGDK_PCH "AdvancedGDK/../../AdvancedGDKPCH.hpp"
#endif

#include <AdvancedGDK/Dependencies/SampGDK.hpp>
#include <AdvancedGDK/Dependencies/QuickMaffs.hpp>

// Core/:
#include <AdvancedGDK/Core/Actions.hpp>
#include <AdvancedGDK/Core/Events.hpp>
#include <AdvancedGDK/Core/Clock.hpp>
#include <AdvancedGDK/Core/Color.hpp>
#include <AdvancedGDK/Core/Exceptions.hpp>
#include <AdvancedGDK/Core/Pointers.hpp>
#include <AdvancedGDK/Core/TypeTraits.hpp>

#include <AdvancedGDK/Core/TextInc.hpp>
#include <AdvancedGDK/Core/ContainerInc.hpp>
#include <AdvancedGDK/Core/BasicInterfacesInc.hpp>


// World/:
#include <AdvancedGDK/World/MapObject.hpp>
#include <AdvancedGDK/World/Scene.hpp>
#include <AdvancedGDK/World/Vehicle.hpp>
#include <AdvancedGDK/World/Map.hpp>
#include <AdvancedGDK/World/SceneLoader.hpp>
#include <AdvancedGDK/World/GangZone.hpp>

// --> World/MapObject/:
#include <AdvancedGDK/World/GlobalObject.hpp>
#include <AdvancedGDK/World/PersonalObject.hpp>
#include <AdvancedGDK/World/UniversalObject.hpp>

// --> World/Streamer/:
#include <AdvancedGDK/World/Streamer/Chunk.hpp>
#include <AdvancedGDK/World/Streamer/ChunkActor.hpp>
#include <AdvancedGDK/World/Streamer/GlobalActorWrapper.hpp>
#include <AdvancedGDK/World/Streamer/GlobalObjectWrapper.hpp>
#include <AdvancedGDK/World/Streamer/VehicleWrapper.hpp>
#include <AdvancedGDK/World/Streamer/PlayerWrapper.hpp>
#include <AdvancedGDK/World/Streamer/StreamerSettings.hpp>
#include <AdvancedGDK/World/Streamer/Streamer.hpp>

// Server/:
#include <AdvancedGDK/Server/Chat.hpp>
#include <AdvancedGDK/Server/GameMode.hpp>
#include <AdvancedGDK/Server/Server.hpp>

// --> Server/Command/:
#include <AdvancedGDK/Server/Command.hpp>
#include <AdvancedGDK/Server/CommandManager.hpp>

// --> Server/Player:
#include <AdvancedGDK/Server/Player.hpp>
#include <AdvancedGDK/Server/PlayerPool.hpp>
#include <AdvancedGDK/Server/Weapon.hpp>
#include <AdvancedGDK/Server/Teleport.hpp>
