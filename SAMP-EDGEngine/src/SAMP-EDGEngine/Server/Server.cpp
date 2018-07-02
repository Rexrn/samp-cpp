#include "SAMP-EDGEnginePCH.hpp"

// Custom includes:
#include <SAMP-EDGEngine/Server/Server.hpp>
#include <SAMP-EDGEngine/Server/GameMode.hpp>
#include <SAMP-EDGEngine/Server/PlayerPool.hpp>
#include <SAMP-EDGEngine/Core/Text/ASCII.hpp>


samp_edgengine::UniquePtr<samp_edgengine::ServerClass>			Server;		// Initialize Server instance.
samp_edgengine::UniquePtr<samp_edgengine::IGameMode>			GameMode;	// Initialize GameMode instance.

namespace samp_edgengine
{
/////////////////////////////////////////////////////////////////////////////////////////
ServerClass::ServerClass()
	:
	m_lastUpdate{}
{
}

/////////////////////////////////////////////////////////////////////////////////////////
ServerClass::~ServerClass()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
void ServerClass::setup(UniquePtr<IGameMode> &&gameMode_)
{
	// Drop previous game mode.
	GameMode.reset();
	if (gameMode_)
	{
		GameMode = std::forward< UniquePtr<IGameMode> >(gameMode_);
		GameMode->setup();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::Default::isPlayerNameValid(const std::string_view name_)
{
	static constexpr const char* cxAvailableCharacters = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789_[]()$@=.";

	return name_.length() >= 3 && name_.length() <= 20
		&& name_.find_first_not_of(cxAvailableCharacters) == std::string_view::npos;
}

/////////////////////////////////////////////////////////////////////////////////////////


	/* TODO: implement vehicles, scenes, checkpoints and tasks.
	GameMode->vehicles.update();
	GameMode->scenes.update();
	GameMode->checkpoints.update();
	GameMode->tasks.update();

	GameMode->update(static_cast<float>((Clock::currentTime() - m_lastUpdate).seconds()));

	m_lastUpdate = Clock::currentTime();
	*/
	


/////////////////////////////////////////////////////////////////////////////////////////
void ServerClass::setDescription(const std::string_view desc_)
{
	// We cannot avoid copying `desc_`, because const char* passed to sampgdk function must be null terminated.
	std::string copy{ desc_ };
	sampgdk_SetGameModeText(copy.c_str());
}

/* TODO: missing implementation.

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnGameModeInit()
{
	return GameMode->onGameModeInit();
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnGameModeExit()
{
	return GameMode->onGameModeExit();
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerConnect(int playerid)
{
	auto player = GameMode->newPlayerInstance(playerid);

	// add player to the list
	GameMode->Players.add(player);
	GameMode->scenes.playerConnected(player);

	return GameMode->onPlayerConnect(player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerDisconnect(int playerid, int reason)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto discReason = static_cast<EDisconnectReason>(reason);

	player->setSpawned(false);

	// Make sure that every object is hidden before player disconnects.
	GameMode->scenes.playerDisconnected(player);
	GameMode->vehicles.playerDisconnected(player);
	GameMode->textdrawRegistry.playerDisconnected(player);

	bool result = GameMode->onPlayerDisconnect(player, discReason);
	// We need to do it anyway (remove from player manager)
	GameMode->Players.remove(player);
	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerSpawn(int playerid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	auto result = GameMode->onPlayerSpawn(player); // TODO: checking

	player->onSpawn();
	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerDeath(int playerid, int killerid, int reason)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto killer = GameMode->Players.findByIndex(killerid);

	player->onDeath();

	auto deathReason = static_cast<Weapon::Type>(reason);

	return GameMode->onPlayerDeath(player, killer, deathReason); // TODO: Checking
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehicleSpawn(int vehicleid)
{
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onVehicleSpawn(vehicle.lock()); // TODO: checking
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehicleDeath(int vehicleid, int killerid)
{
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);
	auto killer = GameMode->Players.findByIndex(killerid);

	auto result = GameMode->onVehicleDeath(vehicle.lock(), killer); // TODO: checking

	if (!std::dynamic_pointer_cast<StaticVehicle>(vehicle.lock()))
	{
		GameMode->vehicles.remove(vehicle.lock());
	}

	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerText(int playerid, const char* text)
{
	auto player = GameMode->Players.findByIndex(playerid);
	std::string strText(text);

	return GameMode->onPlayerSendText(player, strText); // TODO: checking
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerCommandText(int playerid, const char* cmdtext)
{
	auto player = GameMode->Players.findByIndex(playerid);
	std::string strCmd(cmdtext);

	return GameMode->onPlayerSendCommand(player, strCmd); // TODO: checking
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerRequestClass(int playerid, int classid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	return GameMode->onPlayerRequestClass(player, classid); // TODO: checking
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onPlayerEnterVehicle(player, vehicle.lock(), ispassenger);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerExitVehicle(int playerid, int vehicleid)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onPlayerExitVehicle(player, vehicle.lock());
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerStateChange(int playerid, int newstate, int oldstate)
{
	auto player = GameMode->Players.findByIndex(playerid);

	GameMode->vehicles.playerChangedState(player, newstate, oldstate);

	return GameMode->onPlayerStateChange(player, newstate, oldstate);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerEnterCheckpoint(int playerid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	if (auto checkpoint = player->getCheckpoint())
		checkpoint->onPlayerEnter(player);

	return GameMode->onPlayerEnterCheckpoint(player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerLeaveCheckpoint(int playerid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	if (auto checkpoint = player->getCheckpoint())
		checkpoint->onPlayerLeave(player);

	return GameMode->onPlayerLeaveCheckpoint(player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerEnterRaceCheckpoint(int playerid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	if (auto checkpoint = player->getRaceCheckpoint())
		checkpoint->onPlayerEnter(player);

	return GameMode->onPlayerEnterRaceCheckpoint(player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerLeaveRaceCheckpoint(int playerid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	if (auto checkpoint = player->getRaceCheckpoint())
		checkpoint->onPlayerLeave(player);

	return GameMode->onPlayerLeaveRaceCheckpoint(player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnRconCommand(const char* cmd)
{
	std::string rconCmd(cmd);

	return GameMode->onRconCommand(rconCmd);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerRequestSpawn(int playerid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	player->reloadColor();

	return GameMode->onPlayerRequestSpawn(player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnObjectMoved(int objectid)
{
	// TODO: disable this
	return GameMode->onObjectMoved(objectid);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerObjectMoved(int playerid, int objectid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	return GameMode->onPlayerObjectMoved(player, GameMode->scenes.findObject(player, objectid).lock());
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerPickUpPickup(int playerid, int pickupid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	return GameMode->onPlayerPickUpPickup(player, pickupid);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehicleMod(int playerid, int vehicleid, int componentid)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onVehicleMod(player, vehicle.lock(), componentid);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnEnterExitModShop(int playerid, int enterexit, int interiorid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	return GameMode->onEnterExitModShop(player, enterexit, interiorid);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onVehiclePaintjob(player, vehicle.lock(), paintjobid);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehicleRespray(int playerid, int vehicleid, int color1, int color2)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onVehicleRespray(player, vehicle.lock(), color1, color2);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehicleDamageStatusUpdate(int vehicleid, int playerid)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onVehicleDamageStatusUpdate(vehicle.lock(), player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z, float vel_x, float vel_y, float vel_z)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onUnoccupiedVehicleUpdate(vehicle.lock(), player, passenger_seat, Vector3(new_x, new_y, new_z), Vector3(vel_x, vel_y, vel_z));
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerSelectedMenuRow(int playerid, int row)
{
	auto player = GameMode->Players.findByIndex(playerid);

	return GameMode->onPlayerSelectedMenuRow(player, row);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerExitedMenu(int playerid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	return GameMode->onPlayerExitedMenu(player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	return GameMode->onPlayerInteriorChange(player, newinteriorid, oldinteriorid);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys)
{
	auto player = GameMode->Players.findByIndex(playerid);

	int keys = 0, leftRight = 0, upDown = 0;
	sampgdk_GetPlayerKeys(playerid, &keys, &upDown, &leftRight);
	player->getKeyboard().update(keys, upDown, leftRight);

	return GameMode->onPlayerKeyStateChange(player, player->getKeyboard());
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnRconLoginAttempt(const char* ip, const char* password, bool success)
{
	return GameMode->onRconLoginAttempt(std::string(ip), std::string(password), success);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerUpdate(int playerid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	int keys = 0, leftRight = 0, upDown = 0;
	sampgdk_GetPlayerKeys(playerid, &keys, &upDown, &leftRight);
	player->getKeyboard().update(keys, upDown, leftRight);

	return GameMode->onPlayerUpdate(player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerStreamIn(int playerid, int forplayerid)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto forPlayer = GameMode->Players.findByIndex(forplayerid);

	return GameMode->onPlayerStreamIn(player, forPlayer);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerStreamOut(int playerid, int forplayerid)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto forPlayer = GameMode->Players.findByIndex(forplayerid);

	return GameMode->onPlayerStreamOut(player, forPlayer);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehicleStreamIn(int vehicleid, int forplayerid)
{
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);
	auto forPlayer = GameMode->Players.findByIndex(forplayerid);

	return GameMode->onVehicleStreamIn(vehicle.lock(), forPlayer);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehicleStreamOut(int vehicleid, int forplayerid)
{
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);
	auto forPlayer = GameMode->Players.findByIndex(forplayerid);

	return GameMode->onVehicleStreamOut(vehicle.lock(), forPlayer);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnActorStreamIn(int actorid, int forplayerid)
{
	auto forPlayer = GameMode->Players.findByIndex(forplayerid);

	return GameMode->onActorStreamIn(actorid, forPlayer);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnActorStreamOut(int actorid, int forplayerid)
{
	auto forPlayer = GameMode->Players.findByIndex(forplayerid);

	return GameMode->onActorStreamOut(actorid, forPlayer);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char* inputtext)
{
	// TODO: create dialog classes
	auto player = GameMode->Players.findByIndex(playerid);

	return GameMode->onDialogResponse(player, response, listitem, std::string(inputtext));
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid, int bodypart)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto issuer = GameMode->Players.findByIndex(issuerid);

	return GameMode->onPlayerTakeDamage(player, issuer, amount, static_cast<Weapon::Type>(weaponid), bodypart);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid, int bodypart)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto damaged = GameMode->Players.findByIndex(damagedid);

	return GameMode->onPlayerGiveDamage(player, damaged, amount, static_cast<Weapon::Type>(weaponid), bodypart);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerGiveDamageActor(int playerid, int damaged_actorid, float amount, int weaponid, int bodypart)
{
	auto player = GameMode->Players.findByIndex(playerid);

	return GameMode->onPlayerGiveDamageActor(player, damaged_actorid, amount, static_cast<Weapon::Type>(weaponid), bodypart);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerClickMap(int playerid, float fX, float fY, float fZ)
{
	auto player = GameMode->Players.findByIndex(playerid);

	return GameMode->onPlayerClickMap(player, Vector3(fX, fY, fZ));
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerClickTextDraw(int playerid, int clickedid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	GameMode->sendDebug(String::format("Player ", player->getName(), " clicked td: ", clickedid));

	auto weak_textDraw = GameMode->textdrawRegistry.find(clickedid);
	if (auto textDraw = weak_textDraw.lock())
	{
		textDraw->onClick(player);
		return GameMode->onPlayerClickTextDraw(player, textDraw);
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerClickPlayerTextDraw(int playerid, int playertextid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	auto weak_textDraw = GameMode->textdrawRegistry.find(playerid, playertextid);
	if (auto textDraw = weak_textDraw.lock())
	{
		textDraw->onClick(player);
		return GameMode->onPlayerClickPlayerTextDraw(player, textDraw);
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnIncomingConnection(int playerid, const char* ip_address, int port)
{
	// This function is called before onPlayerConnect and thus player was not created yet.
	return GameMode->onIncomingConnection(playerid, std::string(ip_address), port);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnTrailerUpdate(int playerid, int vehicleid)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onTrailerUpdate(player, vehicle.lock());
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehicleSirenStateChange(int playerid, int vehicleid, int newstate)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onVehicleSirenStateChange(player, vehicle.lock(), newstate);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerClickPlayer(int playerid, int clickedplayerid, int source)
{
	auto player = GameMode->Players.findByIndex(playerid);
	auto clicked = GameMode->Players.findByIndex(clickedplayerid);

	return GameMode->onPlayerClickPlayer(player, clicked, source);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ)
{
	auto player = GameMode->Players.findByIndex(playerid);

	return GameMode->onPlayerEditObject(player, playerobject, objectid, response, Vector3(fX, fY, fZ), Vector3(fRotX, fRotY, fRotZ));
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ)
{
	auto player = GameMode->Players.findByIndex(playerid);

	return GameMode->onPlayerEditAttachedObject(player, response, index, modelid, boneid, Vector3(fOffsetX, fOffsetY, fOffsetZ), Vector3(fRotX, fRotY, fRotZ), Vector3(fScaleX, fScaleY, fScaleZ));
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ)
{
	auto player = GameMode->Players.findByIndex(playerid);

	return GameMode->onPlayerSelectObject(player, type, objectid, modelid, Vector3(fX, fY, fZ));
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float fX, float fY, float fZ)
{
	auto player = GameMode->Players.findByIndex(playerid);

	return GameMode->onPlayerWeaponShot(player, static_cast<Weapon::Type>(weaponid), hittype, hitid, Vector3(fX, fY, fZ));
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::_impl_OnPlayerEnterRaceCheckpoint(int playerid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	if (auto checkpoint = player->getRaceCheckpoint())
	{
		if (checkpoint->getType() == RaceCheckpoint::Air || checkpoint->getType() == RaceCheckpoint::AirFinish)
		{
			checkpoint->onPlayerLeave(player);
			return GameMode->onPlayerEnterRaceCheckpoint(player);
		}
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::_impl_OnPlayerLeaveRaceCheckpoint(int playerid)
{
	auto player = GameMode->Players.findByIndex(playerid);

	if (auto checkpoint = player->getRaceCheckpoint())
	{
		if (checkpoint->getType() == RaceCheckpoint::Air || checkpoint->getType() == RaceCheckpoint::AirFinish)
		{
			checkpoint->onPlayerLeave(player);
			return GameMode->onPlayerLeaveRaceCheckpoint(player);
		}
	}
	return true;
}*/

/////////////////////////////////////////////////////////////////////////////////////////
void ServerClass::SampEventListType::onUpdate()
{
	Server->Events.ServerUpdates.emit(Clock::now());
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onGameModeInit()
{
	Server->Events.GameModeInits.emit();
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onGameModeExit()
{
	Server->Events.GameModeExits.emit();
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerConnect(Int32 playerIndex_)
{
	auto& player = GameMode->Players.whenPlayerConnectsEx(
		GameMode->newPlayerInstance( static_cast<std::size_t>(playerIndex_) )
	);
	GameMode->Streamer->whenPlayerJoinsServer(player);
	Server->Events.PlayerConnects.emit(player);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerDisconnect(Int32 playerIndex_, Player::DisconnectReason reason_)
{
	auto& player = *GameMode->Players[static_cast<std::size_t>(playerIndex_)];

	Server->Events.PlayerDisconnects.emit(player);

	// Note: this is very important to tell vehicle, that player is no longer inside
	if (auto vehicle = player.getVehicle())
	{
		vehicle->whenPlayerExits(player);
	}

	GameMode->Streamer->whenPlayerLeavesServer(player);
	GameMode->Players.whenPlayerDisconnectsEx(static_cast<std::size_t>(playerIndex_));
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerSpawn(Int32 playerIndex_)
{
	auto& player = *GameMode->Players[static_cast<std::size_t>(playerIndex_)];

	player.setExistingStatus( Player::ExistingStatus::Spawning );
	
	Server->Events.PlayerSpawns.emit(player);

	player.setExistingStatus( Player::ExistingStatus::Spawned );
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerDeath(Int32 playerIndex_, Int32 killerIndex_, Weapon::Type reason_)
{
	auto& player = *GameMode->Players[static_cast<std::size_t>(playerIndex_)];

	player.setExistingStatus( Player::ExistingStatus::Dead );

	// Killer may be null.
	auto killer = (killerIndex_ == Player::InvalidIndex ? nullptr : GameMode->Players[static_cast<std::size_t>(killerIndex_)]);

	Server->Events.PlayerDies.emit(player, killer, static_cast<Weapon::Type>(reason_));
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onVehicleSpawn(Int32 vehicleHandle_)
{
	auto& vehicle = *GameMode->Map.findVehicleByHandle(vehicleHandle_);

	Server->Events.VehicleSpawns.emit(vehicle);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onVehicleDeath(Int32 vehicleHandle_, Int32 killerIndex_)
{
	auto& vehicle = *GameMode->Map.findVehicleByHandle(vehicleHandle_);
	// Killer may be null.
	auto killer = (killerIndex_ == Player::InvalidIndex ? nullptr : GameMode->Players[static_cast<std::size_t>(killerIndex_)]);

	Server->Events.VehicleDies.emit(vehicle, killer);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerSendText(Int32 playerIndex_, std::string_view text_)
{
	auto& player = *GameMode->Players[static_cast<std::size_t>(playerIndex_)];
	Server->Events.PlayerSendsText.emit(player, std::string(text_));
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerSendCommand(Int32 playerIndex_, std::string_view command_)
{
	auto& player = *GameMode->Players[static_cast<std::size_t>(playerIndex_)];

	Server->Events.PlayerSendsCommandText.emit(player, command_);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerRequestClass(Int32 playerIndex_, Int32 classIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerEnterVehicle(Int32 playerIndex_, Int32 vehicleHandle_, bool isPassenger_)
{
	auto& player = *GameMode->Players[ static_cast<Int32>(playerIndex_) ];

	if ( auto vehicle = GameMode->Map.findVehicleByHandle(static_cast<Int32>(vehicleHandle_)) )
	{
		Server->Events.PlayerStartsToEnterVehicle.emit(player, *vehicle, isPassenger_);
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerExitVehicle(Int32 playerIndex_, Int32 vehicleHandle_)
{
	auto& player = *GameMode->Players[static_cast<Int32>(playerIndex_)];

	if (auto const vehicle = GameMode->Map.findVehicleByHandle(static_cast<Int32>(vehicleHandle_)))
	{
		Server->Events.PlayerStartsToExitVehicle.emit(player, *vehicle);
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerStateChange(Int32 playerIndex_, Int32 newState_, Int32 oldState_)
{
	auto& player = *GameMode->Players[static_cast<Int32>(playerIndex_)];


	if (oldState_ == PLAYER_STATE_DRIVER && newState_ != PLAYER_STATE_DRIVER)
	{
		// For this single moment player have still saved pointer to the vehicle.
		if (auto const vehicle = player.getVehicle())
		{
			Server->Events.PlayerExitedVehicle.emit(player, *vehicle);

			// Note: it is very important to tell vehicle, that it is no longer in use.
			vehicle->whenPlayerExits(player);
		}
		player.setVehicle(nullptr);
	}
	else if (oldState_ == PLAYER_STATE_PASSENGER && newState_ != PLAYER_STATE_PASSENGER)
	{
		// For this single moment player have still saved pointer to the vehicle.
		if (auto const vehicle = player.getVehicle())
		{
			Server->Events.PlayerExitedVehicle.emit(player, *vehicle);
			
			// Note: it is very important to tell vehicle, that it is no longer in use.
			vehicle->whenPlayerExits(player);
		}
		player.setVehicle(nullptr);
	}
	
	// Note: this does not start with "else if", since there is a hypothetical situation,
	// when player changes state from passenger to driver.

	// TODO: confirm that this method works when player is falling with parachute and immediately spawns a vehicle,
	// because it will kill him.
	if (oldState_ != PLAYER_STATE_DRIVER && newState_ == PLAYER_STATE_DRIVER)
	{
		if ( auto const vehicle = GameMode->Map.findVehicleByHandle(player.getClientVehicle()) )
		{
			player.setVehicle(vehicle);

			// Note: it is very important to tell vehicle, that player entered the vehicle.
			vehicle->whenPlayerEnters(player, 0);

			Server->Events.PlayerEnteredVehicle.emit(player, *vehicle, 0);
		}
	}
	else if (oldState_ != PLAYER_STATE_DRIVER && newState_ == PLAYER_STATE_PASSENGER)
	{
		if ( auto const vehicle = GameMode->Map.findVehicleByHandle(player.getClientVehicle()))
		{
			player.setVehicle(vehicle);

			// Note: it is very important to tell vehicle, that player entered the vehicle.
			vehicle->whenPlayerEnters(player, player.getVehicleSeat());

			Server->Events.PlayerEnteredVehicle.emit(player, *vehicle, player.getVehicleSeat());
		}
	}
	
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerEnterCheckpoint(Int32 playerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerLeaveCheckpoint(Int32 playerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerEnterRaceCheckpoint(Int32 playerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerLeaveRaceCheckpoint(Int32 playerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onRconCommand(std::string_view rconCommand_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerRequestSpawn(Int32 playerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onObjectMoved(IMapObject::HandleType pbjectHandle_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerObjectMoved(Int32 playerIndex_, Int32 objectHandle_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerPickUpPickup(Int32 playerIndex_, Int32 pickupHandle_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onVehicleMod(Int32 playerIndex_, Int32 vehicleHandle_, Int32 componentIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerEnterModShop(Int32 playerIndex_, Int32 interiorIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerExitModShop(Int32 playerIndex_, Int32 interiorIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onVehiclePaintjob(Int32 playerIndex_, Int32 vehicleHandle_, Int32 paintjobIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onVehicleRespray(Int32 playerIndex_, Int32 vehicleHandle_, Vehicle::Colors colors_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onVehicleDamageStatusUpdate(Int32 vehicleHandle_, Int32 playerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onUnoccupiedVehicleUpdate(Int32 vehicleHandle_, Int32 playerIndex_, math::Vector3f location_, math::Vector3f velocity_)
{
	return true;
}

bool ServerClass::SampEventListType::onUnoccupiedVehicleUpdate(Int32 vehicleHandle_, Int32 playerIndex_, Int32 passengerSeat_, math::Vector3f location_, math::Vector3f velocity_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerSelectedMenuRow(Int32 playerIndex_, Int32 row_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerExitedMenu(Int32 playerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerInteriorChange(Int32 playerIndex_, Int32 newInterior_, Int32 oldInterior_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerKeyboardStateChange(Int32 playerIndex_, Keyboard const & newState_, Keyboard const & oldState_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onRconLoginAttempt(std::string_view IP_, std::string_view password_, bool success_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerUpdate(Int32 playerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerStreamIn(Int32 playerIndex_, Int32 forPlayerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerStreamOut(Int32 playerIndex_, Int32 forPlayerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onVehicleStreamIn(Int32 vehicleHandle_, Int32 forPlayerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onVehicleStreamOut(Int32 vehicleHandle_, Int32 forPlayerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onActorStreamIn(Int32 actorIndex_, Int32 forPlayerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onActorStreamOut(Int32 actorIndex_, Int32 forPlayerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onDialogResponse(Int32 playerIndex_, Int32 dialogIndex_, Dialog::Button button_, Int32 listItem_, std::string_view inputText_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerTakeDamage(Int32 playerIndex_, Int32 issuerIndex_, float amount_, Weapon::Type weaponIndex_, Player::BodyPart bodyPart_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerGiveDamage(Int32 playerIndex_, Int32 damagedIndex_, float amount_, Weapon::Type weaponIndex_, Player::BodyPart bodyPart_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerGiveDamageActor(Int32 playerIndex_, Int32 damagedActorIndex_, float amount_, Weapon::Type weaponIndex_, Player::BodyPart bodyPart_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerClickMap(Int32 playerIndex_, math::Vector3f location_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerClickTextDraw(Int32 playerIndex_, Int32 textDrawIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerClickPlayerTextDraw(Int32 playerIndex_, Int32 textDrawIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onIncomingConnection(Int32 playerIndex_, std::string_view IPAddress_, Int32 port_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onTrailerUpdate(Int32 playerIndex_, Int32 vehicleHandle_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onVehicleSirenStateChange(Int32 playerIndex_, Int32 vehicleHandle_, bool turnedOn_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerClickPlayer(Int32 playerIndex_, Int32 clickedPlayerIndex_, Int32 source_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerEditObject(Int32 playerIndex_, Int32 objectHandle_, IMapObject::EditResponse response_, math::Vector3f location_, math::Vector3f rotation_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerEditPlayerObject(Int32 playerIndex_, Int32 objectHandle_, IMapObject::EditResponse response_, math::Vector3f location_, math::Vector3f rotation_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerEditAttachedObject(Int32 playerIndex_, bool applied_, Int32 slotIndex_, Int32 modelIndex_, Int32 boneIndex_, math::Vector3f offset_, math::Vector3f rotation_, math::Vector3f scale_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerSelectObject(Int32 playerIndex_, Int32 objectHandle_, Int32 modelIndex_, math::Vector3f location_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerSelectPlayerObject(Int32 playerIndex_, Int32 objectHandle_, Int32 modelIndex_, math::Vector3f location_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::onPlayerWeaponShot(Int32 playerIndex_, Weapon::Type weapon_, Weapon::HitResult hitResult_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::_impl_OnPlayerEnterRaceCheckpoint(Int32 playerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::SampEventListType::_impl_OnPlayerLeaveRaceCheckpoint(Int32 playerIndex_)
{
	return true;
}

} // namespace agdk

extern int main();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return sampgdk_Supports() | SUPPORTS_PROCESS_TICK;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	return sampgdk_Load(ppData);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	sampgdk_Unload();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	sampgdk_ProcessTick();

	if (Server)
		Server->SampEvents.onUpdate();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit()
{
	Server = std::make_unique<samp_edgengine::ServerClass>();

	// call user defined startup method
	main();

	return Server->SampEvents.onGameModeInit();
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeExit()
{
	return Server->SampEvents.onGameModeExit();
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	return Server->SampEvents.onPlayerConnect( playerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	return Server->SampEvents.onPlayerDisconnect( playerid, static_cast<samp_edgengine::Player::DisconnectReason>(reason) );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid)
{
	return Server->SampEvents.onPlayerSpawn( playerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDeath(int playerid, int killerid, int reason)
{
	return Server->SampEvents.onPlayerDeath( playerid, killerid, static_cast<samp_edgengine::Weapon::Type>(reason) );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleSpawn(int vehicleid)
{
	return Server->SampEvents.onVehicleSpawn( vehicleid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDeath(int vehicleid, int killerid)
{
	return Server->SampEvents.onVehicleDeath( vehicleid, killerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerText(int playerid, const char * text)
{
	return Server->SampEvents.onPlayerSendText( playerid, std::string_view{ text } );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char * cmdtext)
{
	return Server->SampEvents.onPlayerSendCommand( playerid, std::string_view{ cmdtext } );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid)
{
	return Server->SampEvents.onPlayerRequestClass( playerid, classid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger)
{
	return Server->SampEvents.onPlayerEnterVehicle( playerid, vehicleid, ispassenger );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitVehicle(int playerid, int vehicleid)
{
	return Server->SampEvents.onPlayerExitVehicle( playerid, vehicleid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStateChange(int playerid, int newstate, int oldstate)
{
	return Server->SampEvents.onPlayerStateChange( playerid, newstate, oldstate );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterCheckpoint(int playerid)
{
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveCheckpoint(int playerid)
{
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterRaceCheckpoint(int playerid)
{
	return Server->SampEvents._impl_OnPlayerEnterRaceCheckpoint(playerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveRaceCheckpoint(int playerid)
{
	return Server->SampEvents._impl_OnPlayerLeaveRaceCheckpoint(playerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnRconCommand(const char * cmd)
{
	return Server->SampEvents.onRconCommand(std::string_view{ cmd });
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestSpawn(int playerid)
{
	return Server->SampEvents.onPlayerRequestSpawn(playerid);
}

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnObjectMoved(int objectid)
{
	return Server->SampEvents.onObjectMoved(objectid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerObjectMoved(int playerid, int objectid)
{
	return Server->SampEvents.onPlayerObjectMoved(playerid, objectid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickUpPickup(int playerid, int pickupid)
{
	return Server->SampEvents.onPlayerPickUpPickup(playerid, pickupid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleMod(int playerid, int vehicleid, int componentid)
{
	return Server->SampEvents.onVehicleMod(playerid, vehicleid, componentid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnEnterExitModShop(int playerid, int enterexit, int interiorid)
{
	if (enterexit == 1)
		return Server->SampEvents.onPlayerEnterModShop(playerid, interiorid);
	else
		return Server->SampEvents.onPlayerExitModShop(playerid, interiorid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid)
{
	return Server->SampEvents.onVehiclePaintjob(playerid, vehicleid, paintjobid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleRespray(int playerid, int vehicleid, int color1, int color2)
{
	return Server->SampEvents.onVehicleRespray( playerid, vehicleid, std::make_pair( color1, color2 ) );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDamageStatusUpdate(int vehicleid, int playerid)
{
	return Server->SampEvents.onVehicleDamageStatusUpdate( vehicleid, playerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z, float vel_x, float vel_y, float vel_z)
{
	if (passenger_seat != 0)
		return Server->SampEvents.onUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, { new_x, new_y, new_z }, { vel_x, vel_y, vel_z });

	return Server->SampEvents.onUnoccupiedVehicleUpdate(vehicleid, playerid, { new_x, new_y, new_z }, { vel_x, vel_y, vel_z });
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectedMenuRow(int playerid, int row)
{
	return Server->SampEvents.onPlayerSelectedMenuRow(playerid, row);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitedMenu(int playerid)
{
	return Server->SampEvents.onPlayerExitedMenu(playerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid)
{
	return Server->SampEvents.onPlayerInteriorChange( playerid, newinteriorid, oldinteriorid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys)
{
	samp_edgengine::Int32 upDown;
	samp_edgengine::Int32 leftRight;
	samp_edgengine::Int32 unusedKeys;
	sampgdk_GetPlayerKeys(playerid, &unusedKeys, &upDown, &leftRight);

	// Note:
	// Old keyboard state has does not ever know whether up/down/left or right key was pressed.
	// TODO: fix this if possible.
	return Server->SampEvents.onPlayerKeyboardStateChange(
		playerid,
		samp_edgengine::Keyboard{ newkeys, upDown, leftRight },
		samp_edgengine::Keyboard{ oldkeys }
	);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnRconLoginAttempt(const char * ip, const char * password, bool success)
{
	return Server->SampEvents.onRconLoginAttempt( std::string_view{ ip }, std::string_view{ password }, success );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerUpdate(int playerid)
{
	return Server->SampEvents.onPlayerUpdate( playerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamIn(int playerid, int forplayerid )
{
	return Server->SampEvents.onPlayerStreamIn( playerid, forplayerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamOut(int playerid, int forplayerid )
{
	return Server->SampEvents.onPlayerStreamOut( playerid, forplayerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamIn(int vehicleid, int forplayerid )
{
	return Server->SampEvents.onVehicleStreamIn( vehicleid, forplayerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamOut(int vehicleid, int forplayerid )
{
	return Server->SampEvents.onVehicleStreamOut( vehicleid, forplayerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnActorStreamIn(int actorid, int forplayerid )
{
	return Server->SampEvents.onActorStreamIn( actorid, forplayerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnActorStreamOut(int actorid, int forplayerid )
{
	return Server->SampEvents.onActorStreamOut( actorid, forplayerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char * inputtext)
{
	return Server->SampEvents.onDialogResponse( playerid, dialogid, static_cast<samp_edgengine::Dialog::Button>(response), listitem, inputtext );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid, int bodypart)
{
	return Server->SampEvents.onPlayerTakeDamage( playerid, issuerid, amount, static_cast<samp_edgengine::Weapon::Type>(weaponid), static_cast<samp_edgengine::Player::BodyPart>(bodypart) );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid, int bodypart)
{
	return Server->SampEvents.onPlayerGiveDamage( playerid, damagedid, amount, static_cast<samp_edgengine::Weapon::Type>(weaponid), static_cast<samp_edgengine::Player::BodyPart>(bodypart) );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerGiveDamageActor(int playerid, int damaged_actorid, float amount, int weaponid, int bodypart)
{
	return Server->SampEvents.onPlayerGiveDamageActor( playerid, damaged_actorid, amount, static_cast<samp_edgengine::Weapon::Type>(weaponid), static_cast<samp_edgengine::Player::BodyPart>(bodypart) );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickMap(int playerid, float fX, float fY, float fZ)
{
	return Server->SampEvents.onPlayerClickMap(playerid, { fX, fY, fZ } );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickTextDraw(int playerid, int clickedid)
{
	return Server->SampEvents.onPlayerClickTextDraw(playerid, clickedid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayerTextDraw(int playerid, int playertextid)
{
	return Server->SampEvents.onPlayerClickPlayerTextDraw(playerid, playertextid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnIncomingConnection(int playerid, const char * ip_address, int port)
{
	return Server->SampEvents.onIncomingConnection(playerid, std::string_view{ ip_address }, port);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnTrailerUpdate(int playerid, int vehicleid)
{
	return Server->SampEvents.onTrailerUpdate(playerid, vehicleid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleSirenStateChange(int playerid, int vehicleid, int newstate)
{
	return Server->SampEvents.onVehicleSirenStateChange(playerid, vehicleid, newstate == 1);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayer(int playerid, int clickedplayerid, int source)
{
	return Server->SampEvents.onPlayerClickPlayer(playerid, clickedplayerid, source);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ)
{
	if (playerobject == 1)
		return Server->SampEvents.onPlayerEditPlayerObject(playerid, objectid, static_cast<samp_edgengine::IMapObject::EditResponse>(response), { fX, fY, fZ }, { fRotX, fRotY, fRotZ });
	else
		return Server->SampEvents.onPlayerEditObject(playerid, objectid, static_cast<samp_edgengine::IMapObject::EditResponse>(response), { fX, fY, fZ }, { fRotX, fRotY, fRotZ });
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ)
{
	return Server->SampEvents.onPlayerEditAttachedObject(playerid, response == 1, index, modelid, boneid, { fOffsetX, fOffsetY, fOffsetZ }, { fRotX, fRotY, fRotZ }, { fScaleX, fScaleY, fScaleZ } );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ)
{
	if (type == SELECT_OBJECT_GLOBAL_OBJECT)
		return Server->SampEvents.onPlayerSelectObject(playerid, objectid, modelid, { fX, fY, fZ } );
	else // if (type == SELECT_OBJECT_PLAYER_OBJECT) // Note: there is currently no other option.
		return Server->SampEvents.onPlayerSelectPlayerObject(playerid, objectid, modelid, { fX, fY, fZ });
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float fX, float fY, float fZ)
{
	return Server->SampEvents.onPlayerWeaponShot(
		playerid,
		static_cast<samp_edgengine::Weapon::Type>(weaponid),
		samp_edgengine::Weapon::HitResult{
			static_cast<samp_edgengine::Weapon::HitResult::Target>(hittype),
			hitid,
			{ fX, fY, fZ }
		}
	);
}
/////////////////////////////////////////////////////////////////////////////////////////