// File description:
// Implements ServerClass behaviour and wraps SAMPGDK callbacks into a class.


#pragma once

// Precompiled header:
#include SAMP_EDGENGINE_PCH

// Custom includes:
#include <SAMP-EDGEngine/Server/PlayerPool.hpp>
#include <SAMP-EDGEngine/Server/Player.hpp>
#include <SAMP-EDGEngine/Server/Weapon.hpp>
#include <SAMP-EDGEngine/Server/Keyboard.hpp>
#include <SAMP-EDGEngine/Server/Dialog.hpp>

#include <SAMP-EDGEngine/World/MapObject.hpp>
#include <SAMP-EDGEngine/World/Vehicle.hpp>
#include <SAMP-EDGEngine/World/Pickup.hpp>

#include <SAMP-EDGEngine/Core/TypesAndDefinitions.hpp>
#include <SAMP-EDGEngine/Core/Pointers.hpp>
#include <SAMP-EDGEngine/Core/Events.hpp>
#include <SAMP-EDGEngine/Core/Clock.hpp>

namespace samp_edgengine
{
// Forward declarations
class IGameMode;

	
/// <summary>
/// Wraps SAMPGDK callback based code into ServerClass class.
/// </summary>
/// <remarks>
/// <para>Own server behaviour can be implemented using `IGameMode` derievation.</para>
/// </remarks>
class ServerClass final
{
public:
	constexpr static chrono::milliseconds CheckpointUpdateInterval{ 50 };
	
	/// <summary>
	/// Initializes a new instance of the <see cref="ServerClass"/> class.
	/// </summary>
	ServerClass();
		
	/// <summary>
	/// Finalizes an instance of the <see cref="ServerClass"/> class.
	/// </summary>
	~ServerClass();
		
	/// <summary>
	/// Prevents from using <see cref="ServerClass"/> copy constructor.
	/// </summary>
	/// <param name="other_">Other instance.</param>
	ServerClass(const ServerClass &other_) = delete;
		
	/// <summary>
	/// Setups the specified gamemode
	/// </summary>
	/// <param name="gameMode_">The gamemode.</param>
	void setup(UniquePtr<IGameMode> &&gameMode_);
		
	/// <summary>
	/// Sets the server description in SAMP client.
	/// </summary>
	/// <param name="desc">The description.</param>
	void setDescription(const std::string_view desc_);
		
private:
	struct SampEventListType {
		void onUpdate();
		bool onGameModeInit();
		bool onGameModeExit();
		bool onPlayerConnect(Int32 playerIndex_);
		bool onPlayerDisconnect(Int32 playerIndex_, Player::DisconnectReason reason_);
		bool onPlayerSpawn(Int32 playerIndex_);
		bool onPlayerDeath(Int32 playerIndex_, Int32 killerIndex_, Weapon::Type reason_);
		bool onVehicleSpawn(Int32 vehicleHandle_);
		bool onVehicleDeath(Int32 vehicleHandle_, Int32 killerIndex_);
		bool onPlayerSendText(Int32 playerIndex_, std::string_view text_);
		bool onPlayerSendCommand(Int32 playerIndex_, std::string_view commandText_);
		bool onPlayerRequestClass(Int32 playerIndex_, Player::ClassIndexType classIndex_);
		bool onPlayerEnterVehicle(Int32 playerIndex_, Int32 vehicleHandle_, bool isPassenger_);
		bool onPlayerExitVehicle(Int32 playerIndex_, Int32 vehicleHandle_);
		bool onPlayerStateChange(Int32 playerIndex_, Int32 newState_, Int32 oldState_);
		bool onPlayerEnterCheckpoint(Int32 playerIndex_);
		bool onPlayerLeaveCheckpoint(Int32 playerIndex_);
		bool onPlayerEnterRaceCheckpoint(Int32 playerIndex_);
		bool onPlayerLeaveRaceCheckpoint(Int32 playerIndex_);
		bool onRconCommand(std::string_view rconCommand_);
		bool onPlayerRequestSpawn(Int32 playerIndex_);
		bool onObjectMoved(Int32 objectHandle_);
		bool onPlayerObjectMoved(Int32 playerIndex_, Int32 objectHandle_);
		bool onPlayerPickUpPickup(Int32 playerIndex_, Int32 pickupHandle_);
		bool onVehicleMod(Int32 playerIndex_, Int32 vehicleHandle_, Int32 componentIndex_);
		bool onPlayerEnterModShop(Int32 playerIndex_, Int32 interiorIndex_);
		bool onPlayerExitModShop(Int32 playerIndex_, Int32 interiorIndex_);
		bool onVehiclePaintjob(Int32 playerIndex_, Int32 vehicleHandle_, Int32 paintjobIndex_);
		bool onVehicleRespray(Int32 playerIndex_, Int32 vehicleHandle_, Vehicle::Colors colors_);
		bool onVehicleDamageStatusUpdate(Int32 vehicleHandle_, Int32 playerIndex_);
		bool onUnoccupiedVehicleUpdate(Int32 vehicleHandle_, Int32 playerIndex_, math::Vector3f location_, math::Vector3f velocity_);
		bool onUnoccupiedVehicleUpdate(Int32 vehicleHandle_, Int32 playerIndex_, Int32 passengerSeat_, math::Vector3f location_, math::Vector3f velocity_);
		bool onPlayerSelectedMenuRow(Int32 playerIndex_, Int32 row_);
		bool onPlayerExitedMenu(Int32 playerIndex_);
		bool onPlayerInteriorChange(Int32 playerIndex_, Int32 newInterior_, Int32 oldInterior);
		bool onPlayerKeyboardStateChange(Int32 playerIndex_, Keyboard const & newState_, Keyboard const & oldState_);
		bool onRconLoginAttempt(std::string_view IP_, std::string_view password_, bool success_);
		bool onPlayerUpdate(Int32 playerIndex_);
		bool onPlayerStreamIn(Int32 playerIndex_, Int32 forPlayerIndex_);
		bool onPlayerStreamOut(Int32 playerIndex_, Int32 forPlayerIndex_);
		bool onVehicleStreamIn(Int32 vehicleHandle_, Int32 forPlayerIndex_);
		bool onVehicleStreamOut(Int32 vehicleHandle_, Int32 forPlayerIndex_);
		bool onActorStreamIn(Int32 actorIndex_, Int32 forPlayerIndex_);
		bool onActorStreamOut(Int32 actorIndex_, Int32 forPlayerIndex_);
		bool onDialogResponse(Int32 playerIndex_, Int32 dialogIndex_, Dialog::Button response, Int32 listItem_, std::string_view inputText_);
		bool onPlayerTakeDamage(Int32 playerIndex_, Int32 issuerIndex_, float amount_, Weapon::Type weapon_, Player::BodyPart bodyPart_);
		bool onPlayerGiveDamage(Int32 playerIndex_, Int32 damagedIndex_, float amount_, Weapon::Type weapon_, Player::BodyPart bodyPart_);
		bool onPlayerGiveDamageActor(Int32 playerIndex_, Int32 damagedActorIndex_, float amount_, Weapon::Type weapon_, Player::BodyPart bodyPart_);
		bool onPlayerClickMap(Int32 playerIndex_, math::Vector3f location_);
		bool onPlayerClickTextDraw(Int32 playerIndex_, Int32 textDrawIndex_);
		bool onPlayerClickPlayerTextDraw(Int32 playerIndex_, Int32 textDrawIndex_);
		bool onIncomingConnection(Int32 playerIndex_, std::string_view IPAddress_, Int32 port_);
		bool onTrailerUpdate(Int32 playerIndex_, Int32 vehicleHandle_);
		bool onVehicleSirenStateChange(Int32 playerIndex_, Int32 vehicleHandle_, bool turnedOn_);
		bool onPlayerClickPlayer(Int32 playerIndex_, Int32 clickedPlayerIndex_, Int32 source_);
		bool onPlayerEditObject(Int32 playerIndex_, Int32 objectHandle_, IMapObject::EditResponse response, math::Vector3f location_, math::Vector3f rotation_);
		bool onPlayerEditPlayerObject(Int32 playerIndex_, Int32 objectHandle_, IMapObject::EditResponse response, math::Vector3f location_, math::Vector3f rotation_);
		bool onPlayerEditAttachedObject(Int32 playerIndex_, bool applied_, Int32 slotIndex_, Int32 modelIndex_, Int32 boneIndex_, math::Vector3f offset_, math::Vector3f rotation_, math::Vector3f scale_);
		bool onPlayerSelectObject(Int32 playerIndex_, Int32 objectHandle_, Int32 modelIndex_, math::Vector3f location_);
		bool onPlayerSelectPlayerObject(Int32 playerIndex_, Int32 objectHandle_, Int32 modelIndex_, math::Vector3f location_);
		bool onPlayerWeaponShot(Int32 playerIndex_, Weapon::Type weapon_, Weapon::HitResult hitResult_);
	};

	struct EventListType
	{
		EventDispatcher<Clock::TimePoint>								onServerUpdate;
		EventDispatcher<>												onGameModeInit;
		EventDispatcher<>												onGameModeExit;
		EventDispatcher<>												onRconCommand;
		EventDispatcher<Player &>										onPlayerConnect;
		EventDispatcher<Player &>										onPlayerDisconnect;
		EventDispatcher<Player &>										onPlayerSpawn;
		EventDispatcher<Player &, Player *, Weapon::Type>				onPlayerDeath;
		EventDispatcher<Vehicle &>										onVehicleSpawn;
		EventDispatcher<Vehicle &, Player *>							onVehicleDeath;
		EventDispatcher<Player &, std::string_view>						onPlayerText;
		EventDispatcher<Player &, std::string_view>						onPlayerCommandText;

		EventDispatcher<Player &, Vehicle &, bool>						onPlayerStartToEnterVehicle;
		EventDispatcher<Player &, Vehicle &>							onPlayerStartToExitVehicle;
		EventDispatcher<Player &, Vehicle &, Int32>						onPlayerEnteredVehicle;
		EventDispatcher<Player &, Vehicle &>							onPlayerExitedVehicle;

		EventDispatcher<Player &>										onPlayerEnterCheckpoint;
		EventDispatcher<Player &>										onPlayerLeaveCheckpoint;
		EventDispatcher<Player &>										onPlayerEnterRaceCheckpoint;
		EventDispatcher<Player &>										onPlayerLeaveRaceCheckpoint;
		/*void onUpdate();
		bool onGameModeInit();
		bool onGameModeExit();
		bool onPlayerConnect(int playerid);
		bool onPlayerDisconnect(int playerid, int reason);
		bool onPlayerSpawn(int playerid);
		bool onPlayerDeath(int playerid, int killerid, int reason);
		bool onVehicleSpawn(int vehicleid);
		bool onVehicleDeath(int vehicleid, int killerid);
		bool onPlayerSendText(int playerid, const char * text);
		bool onPlayerSendCommand(int playerid, const char * cmdtext);
		*/
	};
		
public:
	/////////////////////////////////////////////////////////////////////////////
	class Default
	{
	public:			
		/// <summary>
		/// Checks player name validity.
		/// </summary>
		/// <param name="name_">The name.</param>
		/// <returns>
		///		<c>true</c> if valid; otherwise, <c>false</c>.
		/// </returns>
		/// <remarks>
		/// <para>This is only the default method. You can pass other function to Player::setName method.</para>
		/// </remarks>
		static bool	isPlayerNameValid(const std::string_view name_);
	};

	SampEventListType					SampEvents;
	EventListType						Events;
private:
	
	/// <summary>
	/// Updates the player-checkpoint intersection,
	/// </summary>
	/// <param name="frameTime_">The frame time.</param>
	void updateCheckpoints();

	Clock::TimePoint					m_nextCheckpointUpdate;
	Clock::TimePoint					m_nextUpdate; /// Stores last server update call (used to determine deltaTime).
};

} // namespace agdk

extern samp_edgengine::UniquePtr<samp_edgengine::ServerClass>	Server; /// Global pointer to ServerClass
