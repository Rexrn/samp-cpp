// File description:
// Implements ServerClass behaviour and wraps SAMPGDK callbacks into a class.


#pragma once
#include SAMPEDGENGINE_PCH



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
#include <SAMP-EDGEngine/Core/BasicInterfaces/Updatable.hpp>

namespace samp_cpp
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
	void setup(UniquePtr<IGameMode> gameMode_);
		
	/// <summary>
	/// Sets the server description in SAMP client.
	/// </summary>
	/// <param name="desc">The description.</param>
	void setDescription(const std::string_view desc_);

	/// <summary>
	/// Turns on CJ animations for every player.
	/// </summary>
	void useCJAnimations();
		

	void simulatePlayerSendText(Int32 playerIndex_, std::string_view text_);
	void simulatePlayerSendCommand(Int32 playerIndex_, std::string_view command_);

	// SAMP Events:
	void sampEvent_OnUpdate();
	bool sampEvent_OnGameModeInit();
	bool sampEvent_OnGameModeExit();
	bool sampEvent_OnPlayerConnect(Int32 playerIndex_);
	bool sampEvent_OnPlayerDisconnect(Int32 playerIndex_, Player::DisconnectReason reason_);
	bool sampEvent_OnPlayerSpawn(Int32 playerIndex_);
	bool sampEvent_OnPlayerDeath(Int32 playerIndex_, Int32 killerIndex_, Weapon::Type reason_);
	bool sampEvent_OnVehicleSpawn(Int32 vehicleHandle_);
	bool sampEvent_OnVehicleDeath(Int32 vehicleHandle_, Int32 killerIndex_);
	bool sampEvent_OnPlayerSendText(Int32 playerIndex_, std::string_view text_);
	bool sampEvent_OnPlayerSendCommand(Int32 playerIndex_, std::string_view commandText_);
	bool sampEvent_OnPlayerRequestClass(Int32 playerIndex_, Player::ClassIndexType classIndex_);
	bool sampEvent_OnPlayerEnterVehicle(Int32 playerIndex_, Int32 vehicleHandle_, bool isPassenger_);
	bool sampEvent_OnPlayerExitVehicle(Int32 playerIndex_, Int32 vehicleHandle_);
	bool sampEvent_OnPlayerStateChange(Int32 playerIndex_, Int32 newState_, Int32 oldState_);
	bool sampEvent_OnPlayerEnterCheckpoint(Int32 playerIndex_);
	bool sampEvent_OnPlayerLeaveCheckpoint(Int32 playerIndex_);
	bool sampEvent_OnPlayerEnterRaceCheckpoint(Int32 playerIndex_);
	bool sampEvent_OnPlayerLeaveRaceCheckpoint(Int32 playerIndex_);
	bool sampEvent_OnRconCommand(std::string_view rconCommand_);
	bool sampEvent_OnPlayerRequestSpawn(Int32 playerIndex_);
	bool sampEvent_OnObjectMoved(Int32 objectHandle_);
	bool sampEvent_OnPlayerObjectMoved(Int32 playerIndex_, Int32 objectHandle_);
	bool sampEvent_OnPlayerPickUpPickup(Int32 playerIndex_, Int32 pickupHandle_);
	bool sampEvent_OnVehicleMod(Int32 playerIndex_, Int32 vehicleHandle_, Int32 componentIndex_);
	bool sampEvent_OnPlayerEnterModShop(Int32 playerIndex_, Int32 interiorIndex_);
	bool sampEvent_OnPlayerExitModShop(Int32 playerIndex_, Int32 interiorIndex_);
	bool sampEvent_OnVehiclePaintjob(Int32 playerIndex_, Int32 vehicleHandle_, Int32 paintjobIndex_);
	bool sampEvent_OnVehicleRespray(Int32 playerIndex_, Int32 vehicleHandle_, Vehicle::Colors colors_);
	bool sampEvent_OnVehicleDamageStatusUpdate(Int32 vehicleHandle_, Int32 playerIndex_);
	bool sampEvent_OnUnoccupiedVehicleUpdate(Int32 vehicleHandle_, Int32 playerIndex_, math::Vector3f location_, math::Vector3f velocity_);
	bool sampEvent_OnUnoccupiedVehicleUpdate(Int32 vehicleHandle_, Int32 playerIndex_, Int32 passengerSeat_, math::Vector3f location_, math::Vector3f velocity_);
	bool sampEvent_OnPlayerSelectedMenuRow(Int32 playerIndex_, Int32 row_);
	bool sampEvent_OnPlayerExitedMenu(Int32 playerIndex_);
	bool sampEvent_OnPlayerInteriorChange(Int32 playerIndex_, Int32 newInterior_, Int32 oldInterior);
	bool sampEvent_OnPlayerKeyboardStateChange(Int32 playerIndex_, Keyboard const & newState_, Keyboard const & oldState_);
	bool sampEvent_OnRconLoginAttempt(std::string_view IP_, std::string_view password_, bool success_);
	bool sampEvent_OnPlayerUpdate(Int32 playerIndex_);
	bool sampEvent_OnPlayerStreamIn(Int32 playerIndex_, Int32 forPlayerIndex_);
	bool sampEvent_OnPlayerStreamOut(Int32 playerIndex_, Int32 forPlayerIndex_);
	bool sampEvent_OnVehicleStreamIn(Int32 vehicleHandle_, Int32 forPlayerIndex_);
	bool sampEvent_OnVehicleStreamOut(Int32 vehicleHandle_, Int32 forPlayerIndex_);
	bool sampEvent_OnActorStreamIn(Int32 actorIndex_, Int32 forPlayerIndex_);
	bool sampEvent_OnActorStreamOut(Int32 actorIndex_, Int32 forPlayerIndex_);
	bool sampEvent_OnDialogResponse(Int32 playerIndex_, Int32 dialogIndex_, DialogButton response, Int32 listItem_, std::string_view inputText_);
	bool sampEvent_OnPlayerTakeDamage(Int32 playerIndex_, Int32 issuerIndex_, float amount_, Weapon::Type weapon_, Player::BodyPart bodyPart_);
	bool sampEvent_OnPlayerGiveDamage(Int32 playerIndex_, Int32 damagedIndex_, float amount_, Weapon::Type weapon_, Player::BodyPart bodyPart_);
	bool sampEvent_OnPlayerGiveDamageActor(Int32 playerIndex_, Int32 damagedActorIndex_, float amount_, Weapon::Type weapon_, Player::BodyPart bodyPart_);
	bool sampEvent_OnPlayerClickMap(Int32 playerIndex_, math::Vector3f location_);
	bool sampEvent_OnPlayerClickTextDraw(Int32 playerIndex_, Int32 textDrawIndex_);
	bool sampEvent_OnPlayerClickPlayerTextDraw(Int32 playerIndex_, Int32 textDrawIndex_);
	bool sampEvent_OnIncomingConnection(Int32 playerIndex_, std::string_view IPAddress_, Int32 port_);
	bool sampEvent_OnTrailerUpdate(Int32 playerIndex_, Int32 vehicleHandle_);
	bool sampEvent_OnVehicleSirenStateChange(Int32 playerIndex_, Int32 vehicleHandle_, bool turnedOn_);
	bool sampEvent_OnPlayerClickPlayer(Int32 playerIndex_, Int32 clickedPlayerIndex_, Int32 source_);
	bool sampEvent_OnPlayerEditObject(Int32 playerIndex_, Int32 objectHandle_, IMapObject::EditResponse response, math::Vector3f location_, math::Vector3f rotation_);
	bool sampEvent_OnPlayerEditPlayerObject(Int32 playerIndex_, Int32 objectHandle_, IMapObject::EditResponse response, math::Vector3f location_, math::Vector3f rotation_);
	bool sampEvent_OnPlayerEditAttachedObject(Int32 playerIndex_, bool applied_, Int32 slotIndex_, Int32 modelIndex_, Int32 boneIndex_, math::Vector3f offset_, math::Vector3f rotation_, math::Vector3f scale_);
	bool sampEvent_OnPlayerSelectObject(Int32 playerIndex_, Int32 objectHandle_, Int32 modelIndex_, math::Vector3f location_);
	bool sampEvent_OnPlayerSelectPlayerObject(Int32 playerIndex_, Int32 objectHandle_, Int32 modelIndex_, math::Vector3f location_);
	bool sampEvent_OnPlayerWeaponShot(Int32 playerIndex_, Weapon::Type weapon_, Weapon::HitResult hitResult_);

	EventDispatcher<double, IUpdatable::TimePoint>						onServerUpdate;
	EventDispatcher<>													onGameModeInit;
	EventDispatcher<>													onGameModeExit;
	EventDispatcher<>													onRconCommand;
	EventDispatcher<Player &>											onPlayerConnect;
	EventDispatcher<Player &, Player::DisconnectReason>					onPlayerDisconnect;
	EventDispatcher<Player &>											onPlayerUpdate;
	EventDispatcher<Player &>											onPlayerSpawn;
	EventDispatcher<Player &, Int32>									onPlayerRequestClass;
	EventDispatcher<Player &, Player *, Weapon::Type>					onPlayerDeath;
	EventDispatcher<Vehicle &>											onVehicleSpawn;
	EventDispatcher<Vehicle &, Player *>								onVehicleDeath;
	EventDispatcher<Player &, std::string_view>							onPlayerText;
	EventDispatcher<Player &, std::string_view>							onPlayerCommandText;

	EventDispatcher<Player &, Vehicle &, bool>							onPlayerStartToEnterVehicle;
	EventDispatcher<Player &, Vehicle &>								onPlayerStartToExitVehicle;
	EventDispatcher<Player &, Vehicle &, Int32>							onPlayerEnteredVehicle;
	EventDispatcher<Player &, Vehicle &>								onPlayerExitedVehicle;

	EventDispatcher<Player &>											onPlayerEnterCheckpoint;
	EventDispatcher<Player &>											onPlayerLeaveCheckpoint;
	EventDispatcher<Player &>											onPlayerEnterRaceCheckpoint;
	EventDispatcher<Player &>											onPlayerLeaveRaceCheckpoint;

	EventDispatcher<Player &, Int32, Int32>								onPlayerInteriorChange;
	EventDispatcher<Player &, Keyboard const&, Keyboard const &>		onPlayerKeyboardStateChange;
	EventDispatcher<Player &, DialogButton, Int32, std::string_view>	onDialogResponse;
		
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
	UniquePtr<IGameMode>				GameMode;
private:
	
	/// <summary>
	/// Updates the player-checkpoint intersection,
	/// </summary>
	/// <param name="frameTime_">The frame time.</param>
	void updateCheckpoints();

	bool m_useCJAnimations = false;
	IUpdatable::TimePoint m_nextCheckpointUpdate;
	IUpdatable::TimePoint m_lastUpdate; /// Stores last server update call (used to determine deltaTime).
};

} // namespace agdk

extern samp_cpp::UniquePtr<samp_cpp::ServerClass>	Server; /// Global pointer to ServerClass
