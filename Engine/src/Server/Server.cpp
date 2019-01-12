#include SAMPEDGENGINE_PCH

// Custom includes:
#include <SAMP-EDGEngine/Server/Server.hpp>
#include <SAMP-EDGEngine/Server/GameMode.hpp>
#include <SAMP-EDGEngine/Server/PlayerPool.hpp>
#include <SAMP-EDGEngine/Core/Text/ASCII.hpp>


samp_edgengine::UniquePtr<samp_edgengine::ServerClass>			Server;				// Initialize Server instance.
samp_edgengine::IGameMode*										GameMode = nullptr;	// Initialize GameMode instance.

namespace samp_edgengine
{
/////////////////////////////////////////////////////////////////////////////////////////
ServerClass::ServerClass()
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
	::GameMode = gameMode_.get();
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
void ServerClass::updateCheckpoints()
{
	for (auto player : GameMode->players.getPool())
	{
		if (player)
		{
			if (player->m_insideCheckpoint)
			{
				if (!player->intersectsWithCheckpoint()) // Player was inside checkpoint and now is not.
				{
					player->setInsideCheckpoint(false);
					this->sampEvent_OnPlayerLeaveCheckpoint(player->getIndex());
				}
			}
			else
			{
				if (player->intersectsWithCheckpoint()) // Player wasn't inside checkpoint and now is.
				{
					player->setInsideCheckpoint(true);
					this->sampEvent_OnPlayerEnterCheckpoint(player->getIndex());
				}
			}

			if (player->m_insideRaceCheckpoint)
			{
				if (!player->intersectsWithRaceCheckpoint()) // Player was inside race checkpoint and now is not.
				{
					player->setInsideRaceCheckpoint(false);
					this->sampEvent_OnPlayerLeaveRaceCheckpoint(player->getIndex());
				}
			}
			else
			{
				if (player->intersectsWithRaceCheckpoint()) // Player wasn't inside race checkpoint and now is.
				{
					player->setInsideRaceCheckpoint(true);
					this->sampEvent_OnPlayerEnterRaceCheckpoint(player->getIndex());
				}
			}
		}
	}
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
	GameMode->players.add(player);
	GameMode->scenes.playerConnected(player);

	return GameMode->onPlayerConnect(player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerDisconnect(int playerid, int reason)
{
	auto player = GameMode->players.findByIndex(playerid);
	auto discReason = static_cast<EDisconnectReason>(reason);

	player->setSpawned(false);

	// Make sure that every object is hidden before player disconnects.
	GameMode->scenes.playerDisconnected(player);
	GameMode->vehicles.playerDisconnected(player);
	GameMode->textdrawRegistry.playerDisconnected(player);

	bool result = GameMode->onPlayerDisconnect(player, discReason);
	// We need to do it anyway (remove from player manager)
	GameMode->players.remove(player);
	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerSpawn(int playerid)
{
	auto player = GameMode->players.findByIndex(playerid);

	auto result = GameMode->onPlayerSpawn(player); // TODO: checking

	player->onSpawn();
	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerDeath(int playerid, int killerid, int reason)
{
	auto player = GameMode->players.findByIndex(playerid);
	auto killer = GameMode->players.findByIndex(killerid);

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
	auto killer = GameMode->players.findByIndex(killerid);

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
	auto player = GameMode->players.findByIndex(playerid);
	std::string strText(text);

	return GameMode->onPlayerSendText(player, strText); // TODO: checking
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerCommandText(int playerid, const char* cmdtext)
{
	auto player = GameMode->players.findByIndex(playerid);
	std::string strCmd(cmdtext);

	return GameMode->onPlayerSendCommand(player, strCmd); // TODO: checking
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerRequestClass(int playerid, int classid)
{
	auto player = GameMode->players.findByIndex(playerid);

	return GameMode->onPlayerRequestClass(player, classid); // TODO: checking
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger)
{
	auto player = GameMode->players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onPlayerEnterVehicle(player, vehicle.lock(), ispassenger);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerExitVehicle(int playerid, int vehicleid)
{
	auto player = GameMode->players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onPlayerExitVehicle(player, vehicle.lock());
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerStateChange(int playerid, int newstate, int oldstate)
{
	auto player = GameMode->players.findByIndex(playerid);

	GameMode->vehicles.playerChangedState(player, newstate, oldstate);

	return GameMode->onPlayerStateChange(player, newstate, oldstate);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerEnterCheckpoint(int playerid)
{
	auto player = GameMode->players.findByIndex(playerid);

	if (auto checkpoint = player->getCheckpoint())
		checkpoint->onPlayerEnter(player);

	return GameMode->onPlayerEnterCheckpoint(player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerLeaveCheckpoint(int playerid)
{
	auto player = GameMode->players.findByIndex(playerid);

	if (auto checkpoint = player->getCheckpoint())
		checkpoint->onPlayerLeave(player);

	return GameMode->onPlayerLeaveCheckpoint(player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerEnterRaceCheckpoint(int playerid)
{
	auto player = GameMode->players.findByIndex(playerid);

	if (auto checkpoint = player->getRaceCheckpoint())
		checkpoint->onPlayerEnter(player);

	return GameMode->onPlayerEnterRaceCheckpoint(player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerLeaveRaceCheckpoint(int playerid)
{
	auto player = GameMode->players.findByIndex(playerid);

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
	auto player = GameMode->players.findByIndex(playerid);

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
	auto player = GameMode->players.findByIndex(playerid);

	return GameMode->onPlayerObjectMoved(player, GameMode->scenes.findObject(player, objectid).lock());
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerPickUpPickup(int playerid, int pickupid)
{
	auto player = GameMode->players.findByIndex(playerid);

	return GameMode->onPlayerPickUpPickup(player, pickupid);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehicleMod(int playerid, int vehicleid, int componentid)
{
	auto player = GameMode->players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onVehicleMod(player, vehicle.lock(), componentid);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnEnterExitModShop(int playerid, int enterexit, int interiorid)
{
	auto player = GameMode->players.findByIndex(playerid);

	return GameMode->onEnterExitModShop(player, enterexit, interiorid);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid)
{
	auto player = GameMode->players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onVehiclePaintjob(player, vehicle.lock(), paintjobid);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehicleRespray(int playerid, int vehicleid, int color1, int color2)
{
	auto player = GameMode->players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onVehicleRespray(player, vehicle.lock(), color1, color2);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehicleDamageStatusUpdate(int vehicleid, int playerid)
{
	auto player = GameMode->players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onVehicleDamageStatusUpdate(vehicle.lock(), player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z, float vel_x, float vel_y, float vel_z)
{
	auto player = GameMode->players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onUnoccupiedVehicleUpdate(vehicle.lock(), player, passenger_seat, Vector3(new_x, new_y, new_z), Vector3(vel_x, vel_y, vel_z));
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerSelectedMenuRow(int playerid, int row)
{
	auto player = GameMode->players.findByIndex(playerid);

	return GameMode->onPlayerSelectedMenuRow(player, row);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerExitedMenu(int playerid)
{
	auto player = GameMode->players.findByIndex(playerid);

	return GameMode->onPlayerExitedMenu(player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid)
{
	auto player = GameMode->players.findByIndex(playerid);

	return GameMode->onPlayerInteriorChange(player, newinteriorid, oldinteriorid);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys)
{
	auto player = GameMode->players.findByIndex(playerid);

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
	auto player = GameMode->players.findByIndex(playerid);

	int keys = 0, leftRight = 0, upDown = 0;
	sampgdk_GetPlayerKeys(playerid, &keys, &upDown, &leftRight);
	player->getKeyboard().update(keys, upDown, leftRight);

	return GameMode->onPlayerUpdate(player);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerStreamIn(int playerid, int forplayerid)
{
	auto player = GameMode->players.findByIndex(playerid);
	auto forPlayer = GameMode->players.findByIndex(forplayerid);

	return GameMode->onPlayerStreamIn(player, forPlayer);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerStreamOut(int playerid, int forplayerid)
{
	auto player = GameMode->players.findByIndex(playerid);
	auto forPlayer = GameMode->players.findByIndex(forplayerid);

	return GameMode->onPlayerStreamOut(player, forPlayer);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehicleStreamIn(int vehicleid, int forplayerid)
{
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);
	auto forPlayer = GameMode->players.findByIndex(forplayerid);

	return GameMode->onVehicleStreamIn(vehicle.lock(), forPlayer);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehicleStreamOut(int vehicleid, int forplayerid)
{
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);
	auto forPlayer = GameMode->players.findByIndex(forplayerid);

	return GameMode->onVehicleStreamOut(vehicle.lock(), forPlayer);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnActorStreamIn(int actorid, int forplayerid)
{
	auto forPlayer = GameMode->players.findByIndex(forplayerid);

	return GameMode->onActorStreamIn(actorid, forPlayer);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnActorStreamOut(int actorid, int forplayerid)
{
	auto forPlayer = GameMode->players.findByIndex(forplayerid);

	return GameMode->onActorStreamOut(actorid, forPlayer);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char* inputtext)
{
	// TODO: create dialog classes
	auto player = GameMode->players.findByIndex(playerid);

	return GameMode->onDialogResponse(player, response, listitem, std::string(inputtext));
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid, int bodypart)
{
	auto player = GameMode->players.findByIndex(playerid);
	auto issuer = GameMode->players.findByIndex(issuerid);

	return GameMode->onPlayerTakeDamage(player, issuer, amount, static_cast<Weapon::Type>(weaponid), bodypart);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid, int bodypart)
{
	auto player = GameMode->players.findByIndex(playerid);
	auto damaged = GameMode->players.findByIndex(damagedid);

	return GameMode->onPlayerGiveDamage(player, damaged, amount, static_cast<Weapon::Type>(weaponid), bodypart);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerGiveDamageActor(int playerid, int damaged_actorid, float amount, int weaponid, int bodypart)
{
	auto player = GameMode->players.findByIndex(playerid);

	return GameMode->onPlayerGiveDamageActor(player, damaged_actorid, amount, static_cast<Weapon::Type>(weaponid), bodypart);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerClickMap(int playerid, float fX, float fY, float fZ)
{
	auto player = GameMode->players.findByIndex(playerid);

	return GameMode->onPlayerClickMap(player, Vector3(fX, fY, fZ));
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerClickTextDraw(int playerid, int clickedid)
{
	auto player = GameMode->players.findByIndex(playerid);

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
	auto player = GameMode->players.findByIndex(playerid);

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
	auto player = GameMode->players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onTrailerUpdate(player, vehicle.lock());
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnVehicleSirenStateChange(int playerid, int vehicleid, int newstate)
{
	auto player = GameMode->players.findByIndex(playerid);
	auto vehicle = GameMode->vehicles.findVehicleByIndex(vehicleid);

	return GameMode->onVehicleSirenStateChange(player, vehicle.lock(), newstate);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerClickPlayer(int playerid, int clickedplayerid, int source)
{
	auto player = GameMode->players.findByIndex(playerid);
	auto clicked = GameMode->players.findByIndex(clickedplayerid);

	return GameMode->onPlayerClickPlayer(player, clicked, source);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ)
{
	auto player = GameMode->players.findByIndex(playerid);

	return GameMode->onPlayerEditObject(player, playerobject, objectid, response, Vector3(fX, fY, fZ), Vector3(fRotX, fRotY, fRotZ));
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ)
{
	auto player = GameMode->players.findByIndex(playerid);

	return GameMode->onPlayerEditAttachedObject(player, response, index, modelid, boneid, Vector3(fOffsetX, fOffsetY, fOffsetZ), Vector3(fRotX, fRotY, fRotZ), Vector3(fScaleX, fScaleY, fScaleZ));
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ)
{
	auto player = GameMode->players.findByIndex(playerid);

	return GameMode->onPlayerSelectObject(player, type, objectid, modelid, Vector3(fX, fY, fZ));
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float fX, float fY, float fZ)
{
	auto player = GameMode->players.findByIndex(playerid);

	return GameMode->onPlayerWeaponShot(player, static_cast<Weapon::Type>(weaponid), hittype, hitid, Vector3(fX, fY, fZ));
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::_impl_OnPlayerEnterRaceCheckpoint(int playerid)
{
	auto player = GameMode->players.findByIndex(playerid);

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
	auto player = GameMode->players.findByIndex(playerid);

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
void ServerClass::useCJAnimations()
{
	m_useCJAnimations = true;
}

/////////////////////////////////////////////////////////////////////////////////////////
void ServerClass::sampEvent_OnUpdate()
{
	const_a frameTime = IUpdatable::Clock::now();

	double deltaTime = std::chrono::duration_cast<seconds_d>(frameTime - m_lastUpdate).count();
	m_lastUpdate = frameTime;

	if (GameMode)
	{
		if (Server->m_nextCheckpointUpdate < frameTime)
		{
			Server->m_nextCheckpointUpdate = frameTime + ServerClass::CheckpointUpdateInterval;
			Server->updateCheckpoints();
		}
	}

	Server->onServerUpdate.emit(deltaTime, frameTime);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnGameModeInit()
{
	if (m_useCJAnimations)
		sampgdk_UsePlayerPedAnims();

	Server->onGameModeInit.emit();
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnGameModeExit()
{
	Server->onGameModeExit.emit();

	// Remove game mode.
	Server->setup(nullptr);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerConnect(Int32 playerIndex_)
{
	auto& player = GameMode->players.whenPlayerConnectsEx(
			GameMode->newPlayerInstance( static_cast<std::size_t>(playerIndex_) )
		);
	player.setHealth(100);
	player.setColor(Color::random());
	GameMode->streamer->whenPlayerJoinsServer(player);
	Server->onPlayerConnect.emit(player);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerDisconnect(Int32 playerIndex_, Player::DisconnectReason reason_)
{
	auto& player = *GameMode->players[static_cast<std::size_t>(playerIndex_)];

	Server->onPlayerDisconnect.emit(player, reason_);

	// Note: this is very important to tell vehicle, that player is no longer inside
	if (auto vehicle = player.getVehicle())
	{
		vehicle->whenPlayerExits(player);
	}

	GameMode->streamer->whenPlayerLeavesServer(player);
	GameMode->players.whenPlayerDisconnectsEx(static_cast<std::size_t>(playerIndex_));
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerSpawn(Int32 playerIndex_)
{
	auto& player = *GameMode->players[static_cast<std::size_t>(playerIndex_)];
	player.setHealth(100);
	auto skin = player.getSkin();
	player.setExistingStatus( Player::ExistingStatus::Spawning );
	
	Server->onPlayerSpawn.emit(player);

	player.setExistingStatus( Player::ExistingStatus::Spawned );
	player.setSkin(skin);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerDeath(Int32 playerIndex_, Int32 killerIndex_, Weapon::Type reason_)
{
	auto& player = *GameMode->players[static_cast<std::size_t>(playerIndex_)];

	player.setExistingStatus( Player::ExistingStatus::Dead );

	// Killer may be null.
	auto killer = (killerIndex_ == Player::InvalidIndex ? nullptr : GameMode->players[static_cast<std::size_t>(killerIndex_)]);

	Server->onPlayerDeath.emit(player, killer, static_cast<Weapon::Type>(reason_));
	player.setHealth(100);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnVehicleSpawn(Int32 vehicleHandle_)
{
	auto& vehicle = *GameMode->map.findVehicleByHandle(vehicleHandle_);

	Server->onVehicleSpawn.emit(vehicle);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnVehicleDeath(Int32 vehicleHandle_, Int32 killerIndex_)
{
	auto& vehicle = *GameMode->map.findVehicleByHandle(vehicleHandle_);
	// Killer may be null.
	auto killer = (killerIndex_ == Player::InvalidIndex ? nullptr : GameMode->players[static_cast<std::size_t>(killerIndex_)]);

	Server->onVehicleDeath.emit(vehicle, killer);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerSendText(Int32 playerIndex_, std::string_view text_)
{
	auto& player = *GameMode->players[ playerIndex_ ];
	Server->onPlayerText.emit(player, std::string(text_));
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerSendCommand(Int32 playerIndex_, std::string_view command_)
{
	auto& player = *GameMode->players[ playerIndex_ ];

	Server->onPlayerCommandText.emit(player, command_);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerRequestClass(Int32 playerIndex_, Int32 classIndex_)
{
	auto& player = *GameMode->players[ playerIndex_ ];

	player.setExistingStatus(Player::ExistingStatus::SelectingClass);

	Server->onPlayerRequestClass.emit(player, classIndex_);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerEnterVehicle(Int32 playerIndex_, Int32 vehicleHandle_, bool isPassenger_)
{
	auto& player = *GameMode->players[ static_cast<Int32>(playerIndex_) ];

	if ( auto vehicle = GameMode->map.findVehicleByHandle(static_cast<Int32>(vehicleHandle_)) )
	{
		Server->onPlayerStartToEnterVehicle.emit(player, *vehicle, isPassenger_);
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerExitVehicle(Int32 playerIndex_, Int32 vehicleHandle_)
{
	auto& player = *GameMode->players[static_cast<Int32>(playerIndex_)];

	if (auto const vehicle = GameMode->map.findVehicleByHandle(static_cast<Int32>(vehicleHandle_)))
	{
		Server->onPlayerStartToExitVehicle.emit(player, *vehicle);
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerStateChange(Int32 playerIndex_, Int32 newState_, Int32 oldState_)
{
	auto& player = *GameMode->players[static_cast<Int32>(playerIndex_)];


	if (oldState_ == PLAYER_STATE_DRIVER && newState_ != PLAYER_STATE_DRIVER)
	{
		// For this single moment player have still saved pointer to the vehicle.
		if (auto const vehicle = player.getVehicle())
		{
			Server->onPlayerExitedVehicle.emit(player, *vehicle);

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
			Server->onPlayerExitedVehicle.emit(player, *vehicle);
			
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
		if ( auto const vehicle = GameMode->map.findVehicleByHandle(player.getClientVehicle()) )
		{
			player.setVehicle(vehicle);

			// Note: it is very important to tell vehicle, that player entered the vehicle.
			vehicle->whenPlayerEnters(player, 0);

			Server->onPlayerEnteredVehicle.emit(player, *vehicle, 0);
		}
	}
	else if (oldState_ != PLAYER_STATE_DRIVER && newState_ == PLAYER_STATE_PASSENGER)
	{
		if ( auto const vehicle = GameMode->map.findVehicleByHandle(player.getClientVehicle()))
		{
			player.setVehicle(vehicle);

			// Note: it is very important to tell vehicle, that player entered the vehicle.
			vehicle->whenPlayerEnters(player, player.getVehicleSeat());

			Server->onPlayerEnteredVehicle.emit(player, *vehicle, player.getVehicleSeat());
		}
	}
	
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerEnterCheckpoint(Int32 playerIndex_)
{
	Server->onPlayerEnterCheckpoint.emit( *GameMode->players[playerIndex_] );

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerLeaveCheckpoint(Int32 playerIndex_)
{
	Server->onPlayerLeaveCheckpoint.emit( *GameMode->players[playerIndex_] );
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerEnterRaceCheckpoint(Int32 playerIndex_)
{
	Server->onPlayerEnterRaceCheckpoint.emit( *GameMode->players[playerIndex_] );
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerLeaveRaceCheckpoint(Int32 playerIndex_)
{
	Server->onPlayerLeaveRaceCheckpoint.emit( *GameMode->players[playerIndex_] );
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnRconCommand(std::string_view rconCommand_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerRequestSpawn(Int32 playerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnObjectMoved(IMapObject::HandleType objectHandle_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerObjectMoved(Int32 playerIndex_, Int32 objectHandle_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerPickUpPickup(Int32 playerIndex_, Int32 pickupHandle_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnVehicleMod(Int32 playerIndex_, Int32 vehicleHandle_, Int32 componentIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerEnterModShop(Int32 playerIndex_, Int32 interiorIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerExitModShop(Int32 playerIndex_, Int32 interiorIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnVehiclePaintjob(Int32 playerIndex_, Int32 vehicleHandle_, Int32 paintjobIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnVehicleRespray(Int32 playerIndex_, Int32 vehicleHandle_, Vehicle::Colors colors_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnVehicleDamageStatusUpdate(Int32 vehicleHandle_, Int32 playerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnUnoccupiedVehicleUpdate(Int32 vehicleHandle_, Int32 playerIndex_, math::Vector3f location_, math::Vector3f velocity_)
{
	return true;
}

bool ServerClass::sampEvent_OnUnoccupiedVehicleUpdate(Int32 vehicleHandle_, Int32 playerIndex_, Int32 passengerSeat_, math::Vector3f location_, math::Vector3f velocity_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerSelectedMenuRow(Int32 playerIndex_, Int32 row_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerExitedMenu(Int32 playerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerInteriorChange(Int32 playerIndex_, Int32 newInterior_, Int32 oldInterior_)
{
	auto& player = *GameMode->players[ playerIndex_ ];
	player.syncInterior( newInterior_ );
	Server->onPlayerInteriorChange.emit( player, newInterior_, oldInterior_ );
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerKeyboardStateChange(Int32 playerIndex_, Keyboard const & newState_, Keyboard const & oldState_)
{
	auto& player = *GameMode->players[playerIndex_];
	Server->onPlayerKeyboardStateChange.emit(player, newState_, oldState_);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnRconLoginAttempt(std::string_view IP_, std::string_view password_, bool success_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerUpdate(Int32 playerIndex_)
{
	auto& player = *GameMode->players[playerIndex_];
	Server->onPlayerUpdate.emit(player);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerStreamIn(Int32 playerIndex_, Int32 forPlayerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerStreamOut(Int32 playerIndex_, Int32 forPlayerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnVehicleStreamIn(Int32 vehicleHandle_, Int32 forPlayerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnVehicleStreamOut(Int32 vehicleHandle_, Int32 forPlayerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnActorStreamIn(Int32 actorIndex_, Int32 forPlayerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnActorStreamOut(Int32 actorIndex_, Int32 forPlayerIndex_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnDialogResponse(Int32 playerIndex_, Int32 dialogIndex_, DialogButton button_, Int32 listItem_, std::string_view inputText_)
{
	auto& player = *GameMode->players[playerIndex_];
	if (auto dialog = player.getDialog())
	{
		Server->onDialogResponse.emit(player, button_, listItem_, inputText_);
		dialog->onResponse(button_, listItem_, inputText_);
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerTakeDamage(Int32 playerIndex_, Int32 issuerIndex_, float amount_, Weapon::Type weaponIndex_, Player::BodyPart bodyPart_)
{
	auto& player = *GameMode->players[playerIndex_];
	if (issuerIndex_ == -1)
	{
		player.damage(amount_, samp_edgengine::Weapon::isDamageType(weaponIndex_));
	}
		
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerGiveDamage(Int32 playerIndex_, Int32 damagedIndex_, float amount_, Weapon::Type weaponIndex_, Player::BodyPart bodyPart_)
{
	auto& damaged = *GameMode->players[damagedIndex_];
	damaged.damage(amount_, samp_edgengine::Weapon::isDamageType(weaponIndex_));
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerGiveDamageActor(Int32 playerIndex_, Int32 damagedActorIndex_, float amount_, Weapon::Type weaponIndex_, Player::BodyPart bodyPart_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerClickMap(Int32 playerIndex_, math::Vector3f location_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerClickTextDraw(Int32 playerIndex_, Int32 textDrawIndex_)
{
	if(auto textDraw = GameMode->getTextDraw(textDrawIndex_))
	{
		textDraw->whenPlayerClicks(*GameMode->players[playerIndex_]);
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerClickPlayerTextDraw(Int32 playerIndex_, Int32 textDrawIndex_)
{
	auto& player = *GameMode->players[playerIndex_];
	if (auto textDraw = player.getTextDraw(textDrawIndex_))
	{
		textDraw->whenPlayerClicks();
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnIncomingConnection(Int32 playerIndex_, std::string_view IPAddress_, Int32 port_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnTrailerUpdate(Int32 playerIndex_, Int32 vehicleHandle_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnVehicleSirenStateChange(Int32 playerIndex_, Int32 vehicleHandle_, bool turnedOn_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerClickPlayer(Int32 playerIndex_, Int32 clickedPlayerIndex_, Int32 source_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerEditObject(Int32 playerIndex_, Int32 objectHandle_, IMapObject::EditResponse response_, math::Vector3f location_, math::Vector3f rotation_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerEditPlayerObject(Int32 playerIndex_, Int32 objectHandle_, IMapObject::EditResponse response_, math::Vector3f location_, math::Vector3f rotation_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerEditAttachedObject(Int32 playerIndex_, bool applied_, Int32 slotIndex_, Int32 modelIndex_, Int32 boneIndex_, math::Vector3f offset_, math::Vector3f rotation_, math::Vector3f scale_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerSelectObject(Int32 playerIndex_, Int32 objectHandle_, Int32 modelIndex_, math::Vector3f location_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerSelectPlayerObject(Int32 playerIndex_, Int32 objectHandle_, Int32 modelIndex_, math::Vector3f location_)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool ServerClass::sampEvent_OnPlayerWeaponShot(Int32 playerIndex_, Weapon::Type weapon_, Weapon::HitResult hitResult_)
{
	return true;
}


} // namespace agdk