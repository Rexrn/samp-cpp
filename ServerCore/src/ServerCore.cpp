#include <SAMP-EDGEngine/Everything.hpp>

extern samp_cpp::GameModeSetupResult SAMPGameModeSetup();

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
		Server->sampEvent_OnUpdate();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit()
{
	Server = std::make_unique<samp_cpp::ServerClass>();

	// call user defined startup method
	if (auto pGameMode = SAMPGameModeSetup())
	{
		Server->setup( std::move(pGameMode) );
	}

	return Server->sampEvent_OnGameModeInit();
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeExit()
{
	return Server->sampEvent_OnGameModeExit();
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	return Server->sampEvent_OnPlayerConnect( playerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	return Server->sampEvent_OnPlayerDisconnect( playerid, static_cast<samp_cpp::Player::DisconnectReason>(reason) );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid)
{
	return Server->sampEvent_OnPlayerSpawn( playerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDeath(int playerid, int killerid, int reason)
{
	return Server->sampEvent_OnPlayerDeath( playerid, killerid, static_cast<samp_cpp::Weapon::Type>(reason) );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleSpawn(int vehicleid)
{
	return Server->sampEvent_OnVehicleSpawn( vehicleid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDeath(int vehicleid, int killerid)
{
	return Server->sampEvent_OnVehicleDeath( vehicleid, killerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerText(int playerid, const char * text)
{
	return Server->sampEvent_OnPlayerSendText( playerid, std::string_view{ text } );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char * cmdtext)
{
	return Server->sampEvent_OnPlayerSendCommand( playerid, std::string_view{ cmdtext } );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid)
{
	return Server->sampEvent_OnPlayerRequestClass( playerid, classid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger)
{
	return Server->sampEvent_OnPlayerEnterVehicle( playerid, vehicleid, ispassenger );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitVehicle(int playerid, int vehicleid)
{
	return Server->sampEvent_OnPlayerExitVehicle( playerid, vehicleid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStateChange(int playerid, int newstate, int oldstate)
{
	return Server->sampEvent_OnPlayerStateChange( playerid, newstate, oldstate );
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
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveRaceCheckpoint(int playerid)
{
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnRconCommand(const char * cmd)
{
	return Server->sampEvent_OnRconCommand(std::string_view{ cmd });
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestSpawn(int playerid)
{
	return Server->sampEvent_OnPlayerRequestSpawn(playerid);
}

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnObjectMoved(int objectid)
{
	return Server->sampEvent_OnObjectMoved(objectid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerObjectMoved(int playerid, int objectid)
{
	return Server->sampEvent_OnPlayerObjectMoved(playerid, objectid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickUpPickup(int playerid, int pickupid)
{
	return Server->sampEvent_OnPlayerPickUpPickup(playerid, pickupid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleMod(int playerid, int vehicleid, int componentid)
{
	return Server->sampEvent_OnVehicleMod(playerid, vehicleid, componentid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnEnterExitModShop(int playerid, bool enterexit, int interiorid)
{
	if (enterexit)
		return Server->sampEvent_OnPlayerEnterModShop(playerid, interiorid);
	else
		return Server->sampEvent_OnPlayerExitModShop(playerid, interiorid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid)
{
	return Server->sampEvent_OnVehiclePaintjob(playerid, vehicleid, paintjobid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleRespray(int playerid, int vehicleid, int color1, int color2)
{
	return Server->sampEvent_OnVehicleRespray( playerid, vehicleid, std::make_pair( color1, color2 ) );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDamageStatusUpdate(int vehicleid, int playerid)
{
	return Server->sampEvent_OnVehicleDamageStatusUpdate( vehicleid, playerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z, float vel_x, float vel_y, float vel_z)
{
	if (passenger_seat != 0)
		return Server->sampEvent_OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, { new_x, new_y, new_z }, { vel_x, vel_y, vel_z });

	return Server->sampEvent_OnUnoccupiedVehicleUpdate(vehicleid, playerid, { new_x, new_y, new_z }, { vel_x, vel_y, vel_z });
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectedMenuRow(int playerid, int row)
{
	return Server->sampEvent_OnPlayerSelectedMenuRow(playerid, row);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerExitedMenu(int playerid)
{
	return Server->sampEvent_OnPlayerExitedMenu(playerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid)
{
	return Server->sampEvent_OnPlayerInteriorChange( playerid, newinteriorid, oldinteriorid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys)
{
	samp_cpp::Int32 upDown;
	samp_cpp::Int32 leftRight;
	samp_cpp::Int32 unusedKeys;
	sampgdk_GetPlayerKeys(playerid, &unusedKeys, &upDown, &leftRight);

	// Note:
	// Old keyboard state has does not ever know whether up/down/left or right key was pressed.
	// TODO: fix this if possible.
	return Server->sampEvent_OnPlayerKeyboardStateChange(
		playerid,
		samp_cpp::Keyboard{ newkeys, upDown, leftRight },
		samp_cpp::Keyboard{ oldkeys }
	);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnRconLoginAttempt(const char * ip, const char * password, bool success)
{
	return Server->sampEvent_OnRconLoginAttempt( std::string_view{ ip }, std::string_view{ password }, success );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerUpdate(int playerid)
{
	return Server->sampEvent_OnPlayerUpdate( playerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamIn(int playerid, int forplayerid )
{
	return Server->sampEvent_OnPlayerStreamIn( playerid, forplayerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamOut(int playerid, int forplayerid )
{
	return Server->sampEvent_OnPlayerStreamOut( playerid, forplayerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamIn(int vehicleid, int forplayerid )
{
	return Server->sampEvent_OnVehicleStreamIn( vehicleid, forplayerid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleStreamOut(int vehicleid, int forplayerid )
{
	return Server->sampEvent_OnVehicleStreamOut( vehicleid, forplayerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnActorStreamIn(int actorid, int forplayerid )
{
	return Server->sampEvent_OnActorStreamIn( actorid, forplayerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnActorStreamOut(int actorid, int forplayerid )
{
	return Server->sampEvent_OnActorStreamOut( actorid, forplayerid );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char * inputtext)
{
	return Server->sampEvent_OnDialogResponse( playerid, dialogid, static_cast<samp_cpp::DialogButton>(response), listitem, inputtext );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid, int bodypart)
{
	return Server->sampEvent_OnPlayerTakeDamage( playerid, issuerid, amount, static_cast<samp_cpp::Weapon::Type>(weaponid), static_cast<samp_cpp::Player::BodyPart>(bodypart) );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid, int bodypart)
{
	return Server->sampEvent_OnPlayerGiveDamage( playerid, damagedid, amount, static_cast<samp_cpp::Weapon::Type>(weaponid), static_cast<samp_cpp::Player::BodyPart>(bodypart) );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerGiveDamageActor(int playerid, int damaged_actorid, float amount, int weaponid, int bodypart)
{
	return Server->sampEvent_OnPlayerGiveDamageActor( playerid, damaged_actorid, amount, static_cast<samp_cpp::Weapon::Type>(weaponid), static_cast<samp_cpp::Player::BodyPart>(bodypart) );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickMap(int playerid, float fX, float fY, float fZ)
{
	return Server->sampEvent_OnPlayerClickMap(playerid, { fX, fY, fZ } );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickTextDraw(int playerid, int clickedid)
{
	return Server->sampEvent_OnPlayerClickTextDraw(playerid, clickedid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayerTextDraw(int playerid, int playertextid)
{
	return Server->sampEvent_OnPlayerClickPlayerTextDraw(playerid, playertextid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnIncomingConnection(int playerid, const char * ip_address, int port)
{
	return Server->sampEvent_OnIncomingConnection(playerid, std::string_view{ ip_address }, port);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnTrailerUpdate(int playerid, int vehicleid)
{
	return Server->sampEvent_OnTrailerUpdate(playerid, vehicleid);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleSirenStateChange(int playerid, int vehicleid, int newstate)
{
	return Server->sampEvent_OnVehicleSirenStateChange(playerid, vehicleid, newstate == 1);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayer(int playerid, int clickedplayerid, int source)
{
	return Server->sampEvent_OnPlayerClickPlayer(playerid, clickedplayerid, source);
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ)
{
	if (playerobject == 1)
		return Server->sampEvent_OnPlayerEditPlayerObject(playerid, objectid, static_cast<samp_cpp::IMapObject::EditResponse>(response), { fX, fY, fZ }, { fRotX, fRotY, fRotZ });
	else
		return Server->sampEvent_OnPlayerEditObject(playerid, objectid, static_cast<samp_cpp::IMapObject::EditResponse>(response), { fX, fY, fZ }, { fRotX, fRotY, fRotZ });
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ)
{
	return Server->sampEvent_OnPlayerEditAttachedObject(playerid, response == 1, index, modelid, boneid, { fOffsetX, fOffsetY, fOffsetZ }, { fRotX, fRotY, fRotZ }, { fScaleX, fScaleY, fScaleZ } );
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ)
{
	if (type == SELECT_OBJECT_GLOBAL_OBJECT)
		return Server->sampEvent_OnPlayerSelectObject(playerid, objectid, modelid, { fX, fY, fZ } );
	else // if (type == SELECT_OBJECT_PLAYER_OBJECT) // Note: there is currently no other option.
		return Server->sampEvent_OnPlayerSelectPlayerObject(playerid, objectid, modelid, { fX, fY, fZ });
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float fX, float fY, float fZ)
{
	return Server->sampEvent_OnPlayerWeaponShot(
		playerid,
		static_cast<samp_cpp::Weapon::Type>(weaponid),
		samp_cpp::Weapon::HitResult{
			static_cast<samp_cpp::Weapon::HitResult::Target>(hittype),
			hitid,
			{ fX, fY, fZ }
		}
	);
}
/////////////////////////////////////////////////////////////////////////////////////////