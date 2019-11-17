// File description:
// Implements basic game mode interface.
#pragma once
#include SAMPCPP_PCH



// SAMPCpp includes:

#include <SAMPCpp/Server/Chat.hpp>
#include <SAMPCpp/Server/Weapon.hpp>
#include <SAMPCpp/Server/PlayerPool.hpp>
#include <SAMPCpp/Server/CommandHandler.hpp>
#include <SAMPCpp/Server/GlobalTextDraw.hpp>
#include <SAMPCpp/Server/TextDrawOwner.hpp>
#include <SAMPCpp/World/Map.hpp>

#include <SAMPCpp/Core/BasicInterfaces/Streamer.hpp>
#include <SAMPCpp/Core/BasicInterfaces/Updatable.hpp>
#include <SAMPCpp/Core/Pointers.hpp>
#include <SAMPCpp/Core/Events.hpp>
#include <SAMPCpp/Core/TaskSystem.hpp>

#include <SAMPCpp/Core/Log.hpp>
#include <SAMPCpp/Server/ServerDebugLogOutput.hpp>


namespace samp_cpp
{	

class ServerClass;

/// <summary>
/// Provides abstract interface for every gamemode.
/// </summary>
class IGameMode
	:
	public IEventReceiver,
	public TextDrawOwner<GlobalTextDraw>
{
public:		
	/// <summary>
	/// Initializes a new instance of the <see cref="IGameMode"/> class.
	/// </summary>
	IGameMode(ServerClass & server_);
		
	/// <summary>
	/// Finalizes an instance of the <see cref="IGameMode"/> class.
	/// </summary>
	virtual ~IGameMode();
				
	/// <summary>
	/// Creates new player instance.
	/// </summary>
	/// <param name="playerIndex_">Index of the player.</param>
	/// <returns>
	/// New player instance with specified index.
	/// </returns>
	virtual UniquePtr<Player> newPlayerInstance(Int32 playerIndex_);
		
	/// <summary>
	/// Adds the player class.
	/// </summary>
	/// <param name="modelIndex_">Index of the model.</param>
	/// <param name="location_">The location.</param>
	/// <param name="facingAngle_">The facing angle.</param>
	/// <param name="weapons_">The weapons.</param>
	void addPlayerClass(std::size_t modelIndex_, math::Vector3f const location_, float const facingAngle_, std::array<Weapon, 3> weapons_ = {});

	void sendDeathMessage(Player const* left_, Player const * right_, Weapon::Type weapon_);


	ServerClass& server;

	friend class ServerClass;
protected:
	

	/// <summary>
	/// Setups the game mode.
	/// </summary>
	virtual void setup();

	/// <summary>
	/// Setups the streamer. Override it if you want to use custom streamer.
	/// </summary>
	virtual void setupStreamer();

	/// <summary>
	/// Setups event receiving functions. Very important function!
	/// </summary>
	/// <remarks>
	/// <para>It is executed directly after GameMode creation, USE IT to setup event receivers, that receive events from server!</para>
	/// </remarks>
	virtual void setupEvents() {}

	virtual void onServerUpdate(double deltaTime_, IUpdatable::TimePoint timePoint_);

public:
	PlayerPool				players;
	MapClass				map;
	TaskScheduler			tasks;

#ifdef DEBUG
	Log						debugLog;
#endif

	UniquePtr<ICommandHandler> 	commands;
	UniquePtr<IStreamer>		streamer;
	UniquePtr<IChat>			chat;

private:
#ifdef DEBUG
	ServerDebugLogOutput	m_debugLogOutput;
#endif
};

using GameModeSetupResult = UniquePtr<IGameMode>;

}
extern samp_cpp::IGameMode* GameMode;





