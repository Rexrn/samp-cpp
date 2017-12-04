#include "stdafx.h"

#include <Server/Server.hpp>
#include <Server/GameMode.hpp>

#include <Player/PlayerPool.hpp>

#include <Misc/String.hpp>


std::unique_ptr<agdk::Server>		g_server;		/// Initialize g_server instance.
std::unique_ptr<agdk::IGameMode>	g_gameMode;		/// Initialize g_gameMode instance.

namespace agdk
{
	/////////////////////////////////////////////////////////////////////////////////////////
	Server::Server()
	{
		//g_gameMode.reset(new DefaultGameMode);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	Server::~Server()
	{
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	void Server::setup(std::unique_ptr<IGameMode> &&gameMode_)
	{
		// Drop previous game mode.
		g_gameMode.reset();
		if (gameMode_)
		{
			g_gameMode = std::forward< std::unique_ptr<IGameMode> >(gameMode_);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::Default::isPlayerNameValid(const std::string_view name_)
	{
		static constexpr const char* cxprAvailableCharacters = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789_[]()$@=.";

		return name_.length() >= 3 && name_.length() <= 20
			&& name_.find_first_not_of(cxprAvailableCharacters) == std::string_view::npos;
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	void Server::Update()
	{
		/* TODO: implement vehicles, scenes, checkpoints and tasks.
		g_gameMode->vehicles.update();
		g_gameMode->scenes.update();
		g_gameMode->checkpoints.update();
		g_gameMode->tasks.update();

		g_gameMode->update(static_cast<float>((Clock::currentTime() - m_lastUpdate).seconds()));

		m_lastUpdate = Clock::currentTime();
		*/
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	void Server::setDescription(const std::string_view desc_)
	{
		// We cannot avoid copying `desc_`, because const char* passed to sampgdk function must be null terminated.
		std::string copy{ desc_ };
		sampgdk::SetGameModeText(copy.c_str());
	}

	/* TODO: missing implementation.
	
	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnGameModeInit()
	{
		return g_gameMode->onGameModeInit();
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnGameModeExit()
	{
		return g_gameMode->onGameModeExit();
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerConnect(int playerid)
	{
		auto player = g_gameMode->newPlayerInstance(playerid);

		// add player to the list
		g_gameMode->players.add(player);
		g_gameMode->scenes.playerConnected(player);

		return g_gameMode->onPlayerConnect(player);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerDisconnect(int playerid, int reason)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto discReason = static_cast<EDisconnectReason>(reason);

		player->setSpawned(false);

		// Make sure that every object is hidden before player disconnects.
		g_gameMode->scenes.playerDisconnected(player);
		g_gameMode->vehicles.playerDisconnected(player);
		g_gameMode->textdrawRegistry.playerDisconnected(player);

		bool result = g_gameMode->onPlayerDisconnect(player, discReason);
		// We need to do it anyway (remove from player manager)
		g_gameMode->players.remove(player);
		return result;
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerSpawn(int playerid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		auto result = g_gameMode->onPlayerSpawn(player); // TODO: checking

		player->onSpawn();
		return result;
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerDeath(int playerid, int killerid, int reason)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto killer = g_gameMode->players.findByIndex(killerid);

		player->onDeath();

		auto deathReason = static_cast<Weapon::Type>(reason);

		return g_gameMode->onPlayerDeath(player, killer, deathReason); // TODO: Checking
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnVehicleSpawn(int vehicleid)
	{
		auto vehicle = g_gameMode->vehicles.findVehicleByIndex(vehicleid);

		return g_gameMode->onVehicleSpawn(vehicle.lock()); // TODO: checking
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnVehicleDeath(int vehicleid, int killerid)
	{
		auto vehicle = g_gameMode->vehicles.findVehicleByIndex(vehicleid);
		auto killer = g_gameMode->players.findByIndex(killerid);

		auto result = g_gameMode->onVehicleDeath(vehicle.lock(), killer); // TODO: checking

		if (!std::dynamic_pointer_cast<StaticVehicle>(vehicle.lock()))
		{
			g_gameMode->vehicles.remove(vehicle.lock());
		}

		return result;
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerText(int playerid, const char* text)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		std::string strText(text);

		return g_gameMode->onPlayerText(player, strText); // TODO: checking
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerCommandText(int playerid, const char* cmdtext)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		std::string strCmd(cmdtext);

		return g_gameMode->onPlayerCommandText(player, strCmd); // TODO: checking
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerRequestClass(int playerid, int classid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		return g_gameMode->onPlayerRequestClass(player, classid); // TODO: checking
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto vehicle = g_gameMode->vehicles.findVehicleByIndex(vehicleid);

		return g_gameMode->onPlayerEnterVehicle(player, vehicle.lock(), ispassenger);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerExitVehicle(int playerid, int vehicleid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto vehicle = g_gameMode->vehicles.findVehicleByIndex(vehicleid);

		return g_gameMode->onPlayerExitVehicle(player, vehicle.lock());
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerStateChange(int playerid, int newstate, int oldstate)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		g_gameMode->vehicles.playerChangedState(player, newstate, oldstate);

		return g_gameMode->onPlayerStateChange(player, newstate, oldstate);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerEnterCheckpoint(int playerid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		if (auto checkpoint = player->getCheckpoint())
			checkpoint->onPlayerEnter(player);

		return g_gameMode->onPlayerEnterCheckpoint(player);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerLeaveCheckpoint(int playerid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		if (auto checkpoint = player->getCheckpoint())
			checkpoint->onPlayerLeave(player);

		return g_gameMode->onPlayerLeaveCheckpoint(player);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerEnterRaceCheckpoint(int playerid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		if (auto checkpoint = player->getRaceCheckpoint())
			checkpoint->onPlayerEnter(player);

		return g_gameMode->onPlayerEnterRaceCheckpoint(player);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerLeaveRaceCheckpoint(int playerid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		if (auto checkpoint = player->getRaceCheckpoint())
			checkpoint->onPlayerLeave(player);

		return g_gameMode->onPlayerLeaveRaceCheckpoint(player);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnRconCommand(const char* cmd)
	{
		std::string rconCmd(cmd);

		return g_gameMode->onRconCommand(rconCmd);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerRequestSpawn(int playerid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		player->reloadColor();

		return g_gameMode->onPlayerRequestSpawn(player);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnObjectMoved(int objectid)
	{
		// TODO: disable this
		return g_gameMode->onObjectMoved(objectid);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerObjectMoved(int playerid, int objectid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		return g_gameMode->onPlayerObjectMoved(player, g_gameMode->scenes.findObject(player, objectid).lock());
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerPickUpPickup(int playerid, int pickupid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		return g_gameMode->onPlayerPickUpPickup(player, pickupid);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnVehicleMod(int playerid, int vehicleid, int componentid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto vehicle = g_gameMode->vehicles.findVehicleByIndex(vehicleid);

		return g_gameMode->onVehicleMod(player, vehicle.lock(), componentid);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnEnterExitModShop(int playerid, int enterexit, int interiorid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		return g_gameMode->onEnterExitModShop(player, enterexit, interiorid);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto vehicle = g_gameMode->vehicles.findVehicleByIndex(vehicleid);

		return g_gameMode->onVehiclePaintjob(player, vehicle.lock(), paintjobid);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnVehicleRespray(int playerid, int vehicleid, int color1, int color2)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto vehicle = g_gameMode->vehicles.findVehicleByIndex(vehicleid);

		return g_gameMode->onVehicleRespray(player, vehicle.lock(), color1, color2);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnVehicleDamageStatusUpdate(int vehicleid, int playerid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto vehicle = g_gameMode->vehicles.findVehicleByIndex(vehicleid);

		return g_gameMode->onVehicleDamageStatusUpdate(vehicle.lock(), player);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z, float vel_x, float vel_y, float vel_z)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto vehicle = g_gameMode->vehicles.findVehicleByIndex(vehicleid);

		return g_gameMode->onUnoccupiedVehicleUpdate(vehicle.lock(), player, passenger_seat, Vector3(new_x, new_y, new_z), Vector3(vel_x, vel_y, vel_z));
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerSelectedMenuRow(int playerid, int row)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		return g_gameMode->onPlayerSelectedMenuRow(player, row);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerExitedMenu(int playerid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		return g_gameMode->onPlayerExitedMenu(player);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		return g_gameMode->onPlayerInteriorChange(player, newinteriorid, oldinteriorid);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		int keys = 0, leftRight = 0, upDown = 0;
		sampgdk::GetPlayerKeys(playerid, &keys, &upDown, &leftRight);
		player->getKeyboard().update(keys, upDown, leftRight);

		return g_gameMode->onPlayerKeyStateChange(player, player->getKeyboard());
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnRconLoginAttempt(const char* ip, const char* password, bool success)
	{
		return g_gameMode->onRconLoginAttempt(std::string(ip), std::string(password), success);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerUpdate(int playerid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		int keys = 0, leftRight = 0, upDown = 0;
		sampgdk::GetPlayerKeys(playerid, &keys, &upDown, &leftRight);
		player->getKeyboard().update(keys, upDown, leftRight);

		return g_gameMode->onPlayerUpdate(player);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerStreamIn(int playerid, int forplayerid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto forPlayer = g_gameMode->players.findByIndex(forplayerid);

		return g_gameMode->onPlayerStreamIn(player, forPlayer);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerStreamOut(int playerid, int forplayerid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto forPlayer = g_gameMode->players.findByIndex(forplayerid);

		return g_gameMode->onPlayerStreamOut(player, forPlayer);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnVehicleStreamIn(int vehicleid, int forplayerid)
	{
		auto vehicle = g_gameMode->vehicles.findVehicleByIndex(vehicleid);
		auto forPlayer = g_gameMode->players.findByIndex(forplayerid);

		return g_gameMode->onVehicleStreamIn(vehicle.lock(), forPlayer);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnVehicleStreamOut(int vehicleid, int forplayerid)
	{
		auto vehicle = g_gameMode->vehicles.findVehicleByIndex(vehicleid);
		auto forPlayer = g_gameMode->players.findByIndex(forplayerid);

		return g_gameMode->onVehicleStreamOut(vehicle.lock(), forPlayer);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnActorStreamIn(int actorid, int forplayerid)
	{
		auto forPlayer = g_gameMode->players.findByIndex(forplayerid);

		return g_gameMode->onActorStreamIn(actorid, forPlayer);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnActorStreamOut(int actorid, int forplayerid)
	{
		auto forPlayer = g_gameMode->players.findByIndex(forplayerid);

		return g_gameMode->onActorStreamOut(actorid, forPlayer);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char* inputtext)
	{
		// TODO: create dialog classes
		auto player = g_gameMode->players.findByIndex(playerid);

		return g_gameMode->onDialogResponse(player, response, listitem, std::string(inputtext));
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid, int bodypart)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto issuer = g_gameMode->players.findByIndex(issuerid);

		return g_gameMode->onPlayerTakeDamage(player, issuer, amount, static_cast<Weapon::Type>(weaponid), bodypart);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid, int bodypart)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto damaged = g_gameMode->players.findByIndex(damagedid);

		return g_gameMode->onPlayerGiveDamage(player, damaged, amount, static_cast<Weapon::Type>(weaponid), bodypart);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerGiveDamageActor(int playerid, int damaged_actorid, float amount, int weaponid, int bodypart)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		return g_gameMode->onPlayerGiveDamageActor(player, damaged_actorid, amount, static_cast<Weapon::Type>(weaponid), bodypart);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerClickMap(int playerid, float fX, float fY, float fZ)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		return g_gameMode->onPlayerClickMap(player, Vector3(fX, fY, fZ));
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerClickTextDraw(int playerid, int clickedid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		g_gameMode->sendDebug(String::format("Player ", player->getName(), " clicked td: ", clickedid));

		auto weak_textDraw = g_gameMode->textdrawRegistry.find(clickedid);
		if (auto textDraw = weak_textDraw.lock())
		{
			textDraw->onClick(player);
			return g_gameMode->onPlayerClickTextDraw(player, textDraw);
		}
		return false;
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerClickPlayerTextDraw(int playerid, int playertextid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		auto weak_textDraw = g_gameMode->textdrawRegistry.find(playerid, playertextid);
		if (auto textDraw = weak_textDraw.lock())
		{
			textDraw->onClick(player);
			return g_gameMode->onPlayerClickPlayerTextDraw(player, textDraw);
		}
		return false;
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnIncomingConnection(int playerid, const char* ip_address, int port)
	{
		// This function is called before onPlayerConnect and thus player was not created yet.
		return g_gameMode->onIncomingConnection(playerid, std::string(ip_address), port);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnTrailerUpdate(int playerid, int vehicleid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto vehicle = g_gameMode->vehicles.findVehicleByIndex(vehicleid);

		return g_gameMode->onTrailerUpdate(player, vehicle.lock());
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnVehicleSirenStateChange(int playerid, int vehicleid, int newstate)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto vehicle = g_gameMode->vehicles.findVehicleByIndex(vehicleid);

		return g_gameMode->onVehicleSirenStateChange(player, vehicle.lock(), newstate);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerClickPlayer(int playerid, int clickedplayerid, int source)
	{
		auto player = g_gameMode->players.findByIndex(playerid);
		auto clicked = g_gameMode->players.findByIndex(clickedplayerid);

		return g_gameMode->onPlayerClickPlayer(player, clicked, source);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		return g_gameMode->onPlayerEditObject(player, playerobject, objectid, response, Vector3(fX, fY, fZ), Vector3(fRotX, fRotY, fRotZ));
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		return g_gameMode->onPlayerEditAttachedObject(player, response, index, modelid, boneid, Vector3(fOffsetX, fOffsetY, fOffsetZ), Vector3(fRotX, fRotY, fRotZ), Vector3(fScaleX, fScaleY, fScaleZ));
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		return g_gameMode->onPlayerSelectObject(player, type, objectid, modelid, Vector3(fX, fY, fZ));
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float fX, float fY, float fZ)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		return g_gameMode->onPlayerWeaponShot(player, static_cast<Weapon::Type>(weaponid), hittype, hitid, Vector3(fX, fY, fZ));
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::_impl_OnPlayerEnterRaceCheckpoint(int playerid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		if (auto checkpoint = player->getRaceCheckpoint())
		{
			if (checkpoint->getType() == RaceCheckpoint::Air || checkpoint->getType() == RaceCheckpoint::AirFinish)
			{
				checkpoint->onPlayerLeave(player);
				return g_gameMode->onPlayerEnterRaceCheckpoint(player);
			}
		}
		return true;
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	bool Server::_impl_OnPlayerLeaveRaceCheckpoint(int playerid)
	{
		auto player = g_gameMode->players.findByIndex(playerid);

		if (auto checkpoint = player->getRaceCheckpoint())
		{
			if (checkpoint->getType() == RaceCheckpoint::Air || checkpoint->getType() == RaceCheckpoint::AirFinish)
			{
				checkpoint->onPlayerLeave(player);
				return g_gameMode->onPlayerLeaveRaceCheckpoint(player);
			}
		}
		return true;
	}*/
}

extern int main();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return sampgdk::Supports() | SUPPORTS_PROCESS_TICK;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	return sampgdk::Load(ppData);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	sampgdk::Unload();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	sampgdk::ProcessTick();

	if (g_server)
		g_server->Update();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit()
{
	g_server.reset(new agdk::Server);

	// call user defined startup method
	main();

	return g_server->OnGameModeInit();
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeExit()
{
	return g_server->OnGameModeExit();
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	return g_server->OnPlayerConnect(playerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	return g_server->OnPlayerDisconnect(playerid, reason);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid)
{
	return g_server->OnPlayerSpawn(playerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDeath(int playerid, int killerid, int reason)
{
	return g_server->OnPlayerDeath(playerid, killerid, reason);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleSpawn(int vehicleid)
{
	return g_server->OnVehicleSpawn(vehicleid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDeath(int vehicleid, int killerid)
{
	return g_server->OnVehicleDeath(vehicleid, killerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerText(int playerid, const char * text)
{
	return g_server->OnPlayerText(playerid, text);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char * cmdtext)
{
	return g_server->OnPlayerCommandText(playerid, cmdtext);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid)
{
	return g_server->OnPlayerRequestClass(playerid, classid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger)
{
	return g_server->OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitVehicle(int playerid, int vehicleid)
{
	return g_server->OnPlayerExitVehicle(playerid, vehicleid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStateChange(int playerid, int newstate, int oldstate)
{
	return g_server->OnPlayerStateChange(playerid, newstate, oldstate);
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
	return g_server->_impl_OnPlayerEnterRaceCheckpoint(playerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveRaceCheckpoint(int playerid)
{
	return g_server->_impl_OnPlayerLeaveRaceCheckpoint(playerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnRconCommand(const char * cmd)
{
	return g_server->OnRconCommand(cmd);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestSpawn(int playerid)
{
	return g_server->OnPlayerRequestSpawn(playerid);
}

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnObjectMoved(int objectid)
{
	return g_server->OnObjectMoved(objectid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerObjectMoved(int playerid, int objectid)
{
	return g_server->OnPlayerObjectMoved(playerid, objectid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickUpPickup(int playerid, int pickupid)
{
	return g_server->OnPlayerPickUpPickup(playerid, pickupid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleMod(int playerid, int vehicleid, int componentid)
{
	return g_server->OnVehicleMod(playerid, vehicleid, componentid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnEnterExitModShop(int playerid, int enterexit, int interiorid)
{
	return g_server->OnEnterExitModShop(playerid, enterexit, interiorid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid)
{
	return g_server->OnVehiclePaintjob(playerid, vehicleid, paintjobid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleRespray(int playerid, int vehicleid, int color1, int color2)
{
	return g_server->OnVehicleRespray(playerid, vehicleid, color1, color2);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDamageStatusUpdate(int vehicleid, int playerid)
{
	return g_server->OnVehicleDamageStatusUpdate(vehicleid, playerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z, float vel_x, float vel_y, float vel_z)
{
	return g_server->OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, new_x, new_y, new_z, vel_x, vel_y, vel_z);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectedMenuRow(int playerid, int row)
{
	return g_server->OnPlayerSelectedMenuRow(playerid, row);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitedMenu(int playerid)
{
	return g_server->OnPlayerExitedMenu(playerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid)
{
	return g_server->OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys)
{
	return g_server->OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnRconLoginAttempt(const char * ip, const char * password, bool success)
{
	return g_server->OnRconLoginAttempt(ip, password, success);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerUpdate(int playerid)
{
	return g_server->OnPlayerUpdate(playerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamIn(int playerid, int forplayerid)
{
	return g_server->OnPlayerStreamIn(playerid, forplayerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamOut(int playerid, int forplayerid)
{
	return g_server->OnPlayerStreamOut(playerid, forplayerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamIn(int vehicleid, int forplayerid)
{
	return g_server->OnVehicleStreamIn(vehicleid, forplayerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamOut(int vehicleid, int forplayerid)
{
	return g_server->OnVehicleStreamOut(vehicleid, forplayerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnActorStreamIn(int actorid, int forplayerid)
{
	return g_server->OnActorStreamIn(actorid, forplayerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnActorStreamOut(int actorid, int forplayerid)
{
	return g_server->OnActorStreamOut(actorid, forplayerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char * inputtext)
{
	return g_server->OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid, int bodypart)
{
	return g_server->OnPlayerTakeDamage(playerid, issuerid, amount, weaponid, bodypart);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid, int bodypart)
{
	return g_server->OnPlayerGiveDamage(playerid, damagedid, amount, weaponid, bodypart);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerGiveDamageActor(int playerid, int damaged_actorid, float amount, int weaponid, int bodypart)
{
	return g_server->OnPlayerGiveDamageActor(playerid, damaged_actorid, amount, weaponid, bodypart);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickMap(int playerid, float fX, float fY, float fZ)
{
	return g_server->OnPlayerClickMap(playerid, fX, fY, fZ);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickTextDraw(int playerid, int clickedid)
{
	return g_server->OnPlayerClickTextDraw(playerid, clickedid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayerTextDraw(int playerid, int playertextid)
{
	return g_server->OnPlayerClickPlayerTextDraw(playerid, playertextid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnIncomingConnection(int playerid, const char * ip_address, int port)
{
	return g_server->OnIncomingConnection(playerid, ip_address, port);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnTrailerUpdate(int playerid, int vehicleid)
{
	return g_server->OnTrailerUpdate(playerid, vehicleid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleSirenStateChange(int playerid, int vehicleid, int newstate)
{
	return g_server->OnVehicleSirenStateChange(playerid, vehicleid, newstate);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayer(int playerid, int clickedplayerid, int source)
{
	return g_server->OnPlayerClickPlayer(playerid, clickedplayerid, source);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ)
{
	return g_server->OnPlayerEditObject(playerid, playerobject, objectid, response, fX, fY, fZ, fRotX, fRotY, fRotZ);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ)
{
	return g_server->OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ)
{
	return g_server->OnPlayerSelectObject(playerid, type, objectid, modelid, fX, fY, fZ);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float fX, float fY, float fZ)
{
	return g_server->OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, fX, fY, fZ);
}
/////////////////////////////////////////////////////////////////////////////////////////