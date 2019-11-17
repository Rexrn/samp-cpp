// File description:
// Includes the entire SAMPCpp.
#pragma once

#ifndef SAMPCPP_PCH
#define SAMPCPP_PCH <SAMPCpp/EnginePCH.hpp>
#endif
#include SAMPCPP_PCH

#include <SAMPCpp/Dependencies/SampGDK.hpp>
#include <SAMPCpp/Dependencies/QuickMaffs.hpp>

// Core/:
#include <SAMPCpp/Core/TaskSystem.hpp>
#include <SAMPCpp/Core/Events.hpp>
#include <SAMPCpp/Core/Clock.hpp>
#include <SAMPCpp/Core/Color.hpp>
#include <SAMPCpp/Core/Exceptions.hpp>
#include <SAMPCpp/Core/Pointers.hpp>
#include <SAMPCpp/Core/TypeTraits.hpp>
#include <SAMPCpp/Core/Log.hpp>


#include <SAMPCpp/Core/TextInc.hpp>
#include <SAMPCpp/Core/ContainerInc.hpp>
#include <SAMPCpp/Core/BasicInterfacesInc.hpp>


// World/:
#include <SAMPCpp/World/MapObject.hpp>
#include <SAMPCpp/World/Scene.hpp>
#include <SAMPCpp/World/Vehicle.hpp>
#include <SAMPCpp/World/Map.hpp>
#include <SAMPCpp/World/GangZone.hpp>
#include <SAMPCpp/World/Checkpoint.hpp>
#include <SAMPCpp/World/RaceCheckpoint.hpp>

// --> World/MapObject/:
#include <SAMPCpp/World/GlobalObject.hpp>
#include <SAMPCpp/World/PersonalObject.hpp>
#include <SAMPCpp/World/UniversalObject.hpp>

// --> World/Streamer/:
#include <SAMPCpp/World/Streamer/Chunk.hpp>
#include <SAMPCpp/World/Streamer/ChunkActor.hpp>
#include <SAMPCpp/World/Streamer/GlobalActorWrapper.hpp>
#include <SAMPCpp/World/Streamer/GlobalObjectWrapper.hpp>
#include <SAMPCpp/World/Streamer/VehicleWrapper.hpp>
#include <SAMPCpp/World/Streamer/PlayerWrapper.hpp>
#include <SAMPCpp/World/Streamer/StreamerSettings.hpp>
#include <SAMPCpp/World/Streamer/Streamer.hpp>

// Server/:
#include <SAMPCpp/Server/Chat.hpp>
#include <SAMPCpp/Server/GameMode.hpp>
#include <SAMPCpp/Server/GameModeChild.hpp>
#include <SAMPCpp/Server/Server.hpp>
#include <SAMPCpp/Server/TextDraw.hpp>
#include <SAMPCpp/Server/PlayerTextDraw.hpp>
#include <SAMPCpp/Server/GlobalTextDraw.hpp>
#include <SAMPCpp/Server/PlayerTextDrawPanel.hpp>
#include <SAMPCpp/Server/GlobalTextDrawPanel.hpp>

#include <SAMPCpp/Server/ServerDebugLog.hpp>


// --> Server/Command/:
#include <SAMPCpp/Server/Command.hpp>
#include <SAMPCpp/Server/CommandHandler.hpp>

// --> Server/Player:
#include <SAMPCpp/Server/Player.hpp>
#include <SAMPCpp/Server/PlayerPool.hpp>
#include <SAMPCpp/Server/Weapon.hpp>
#include <SAMPCpp/Server/Teleport.hpp>

#include <SAMPCpp/Server/Dialog.hpp>

// TODO: sort and make sure everything is added here.
