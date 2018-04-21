// File description:
// Includes the whole ADVANCEDGDK library.

#pragma once

#ifndef ADVANCEDGDK_PCH
#define ADVANCEDGDK_PCH "AdvancedGDK/../../AdvancedGDKPCH.hpp"
#endif

#include <AdvancedGDK/Compilation/SampGDK.hpp>

// Core/:
#include <AdvancedGDK/Core/Actions.hpp>
#include <AdvancedGDK/Core/Events.hpp>
#include <AdvancedGDK/Core/Clock.hpp>
#include <AdvancedGDK/Core/Color.hpp>
#include <AdvancedGDK/Core/Exceptions.hpp>
#include <AdvancedGDK/Core/Pointers.hpp>
#include <AdvancedGDK/Core/TypeTraits.hpp>

#include <AdvancedGDK/Core/MathInc.hpp>
#include <AdvancedGDK/Core/TextInc.hpp>
#include <AdvancedGDK/Core/ContainerInc.hpp>
#include <AdvancedGDK/Core/BasicInterfacesInc.hpp>


// World/:
#include <AdvancedGDK/World/MapObject.hpp>
#include <AdvancedGDK/World/Scene.hpp>
#include <AdvancedGDK/World/Streaming/ChunkActor.hpp>
#include <AdvancedGDK/World/Chunk.hpp>

// --> World/Vehicle/:
#include <AdvancedGDK/World/Vehicle/Vehicle.hpp>
#include <AdvancedGDK/World/Vehicle/VehiclePool.hpp>

// --> World/MapObject/:
#include <AdvancedGDK/World/MapObject/GlobalObject.hpp>
#include <AdvancedGDK/World/MapObject/PersonalObject.hpp>
#include <AdvancedGDK/World/MapObject/StreamableObject.hpp>
#include <AdvancedGDK/World/MapObject/UniversalObject.hpp>

// Server/:
#include <AdvancedGDK/Server/Chat.hpp>
#include <AdvancedGDK/Server/GameMode.hpp>
#include <AdvancedGDK/Server/Server.hpp>

// --> Server/Command/:
#include <AdvancedGDK/Server/Command/Command.hpp>
#include <AdvancedGDK/Server/Command/CommandManager.hpp>

// --> Server/Player:
#include <AdvancedGDK/Server/Player/Player.hpp>
#include <AdvancedGDK/Server/Player/PlayerPool.hpp>
#include <AdvancedGDK/Server/Player/Weapon.hpp>
#include <AdvancedGDK/Server/Player/Teleport.hpp>
