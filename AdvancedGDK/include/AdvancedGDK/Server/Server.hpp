// File description:
// Implements Server behaviour and wraps SAMPGDK callbacks into a class.


#pragma once

// Precompiled header:
#include "../../../stdafx.h"

// Custom includes:
#include <AdvancedGDK/Misc/Clock.hpp>

namespace agdk
{
	/* Forward declarations */
	class IGameMode;

	
	/// <summary>
	/// Wraps SAMPGDK callback based code into Server class.
	/// </summary>
	/// <remarks>
	/// <para>Own server behaviour can be implemented using `IGameMode` derievation.</para>
	/// </remarks>
	class Server final
	{
	public:
		
		/// <summary>
		/// Initializes a new instance of the <see cref="Server"/> class.
		/// </summary>
		Server();
		
		/// <summary>
		/// Finalizes an instance of the <see cref="Server"/> class.
		/// </summary>
		~Server();
		
		/// <summary>
		/// Prevents from using <see cref="Server"/> copy constructor.
		/// </summary>
		/// <param name="other_">Other instance.</param>
		Server(const Server &other_) = delete;
		
		/// <summary>
		/// Setups the specified gamemode
		/// </summary>
		/// <param name="gameMode_">The gamemode.</param>
		void setup(std::unique_ptr<IGameMode> &&gameMode_);
		
		/// <summary>
		/// Sets the server description in SAMP client.
		/// </summary>
		/// <param name="desc">The description.</param>
		void setDescription(const std::string_view desc_);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////// SAMPGDK core methods //////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void sampEventUpdate();

		bool sampEventOnGameModeInit();
		bool sampEventOnGameModeExit();
		bool sampEventOnPlayerConnect(int playerid);
		bool sampEventOnPlayerDisconnect(int playerid, int reason);
		bool sampEventOnPlayerSpawn(int playerid);
		bool sampEventOnPlayerDeath(int playerid, int killerid, int reason);
		bool sampEventOnVehicleSpawn(int vehicleid);
		bool sampEventOnVehicleDeath(int vehicleid, int killerid);
		bool sampEventOnPlayerText(int playerid, const char * text);
		bool sampEventOnPlayerCommandText(int playerid, const char * cmdtext);
		bool sampEventOnPlayerRequestClass(int playerid, int classid);
		bool sampEventOnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger);
		bool sampEventOnPlayerExitVehicle(int playerid, int vehicleid);
		bool sampEventOnPlayerStateChange(int playerid, int newstate, int oldstate);
		bool sampEventOnPlayerEnterCheckpoint(int playerid);
		bool sampEventOnPlayerLeaveCheckpoint(int playerid);
		bool sampEventOnPlayerEnterRaceCheckpoint(int playerid);
		bool sampEventOnPlayerLeaveRaceCheckpoint(int playerid);
		bool sampEventOnRconCommand(const char * cmd);
		bool sampEventOnPlayerRequestSpawn(int playerid);
		bool sampEventOnObjectMoved(int objectid);
		bool sampEventOnPlayerObjectMoved(int playerid, int objectid);
		bool sampEventOnPlayerPickUpPickup(int playerid, int pickupid);
		bool sampEventOnVehicleMod(int playerid, int vehicleid, int componentid);
		bool sampEventOnEnterExitModShop(int playerid, int enterexit, int interiorid);
		bool sampEventOnVehiclePaintjob(int playerid, int vehicleid, int paintjobid);
		bool sampEventOnVehicleRespray(int playerid, int vehicleid, int color1, int color2);
		bool sampEventOnVehicleDamageStatusUpdate(int vehicleid, int playerid);
		bool sampEventOnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z, float vel_x, float vel_y, float vel_z);
		bool sampEventOnPlayerSelectedMenuRow(int playerid, int row);
		bool sampEventOnPlayerExitedMenu(int playerid);
		bool sampEventOnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid);
		bool sampEventOnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys);
		bool sampEventOnRconLoginAttempt(const char * ip, const char * password, bool success);
		bool sampEventOnPlayerUpdate(int playerid);
		bool sampEventOnPlayerStreamIn(int playerid, int forplayerid);
		bool sampEventOnPlayerStreamOut(int playerid, int forplayerid);
		bool sampEventOnVehicleStreamIn(int vehicleid, int forplayerid);
		bool sampEventOnVehicleStreamOut(int vehicleid, int forplayerid);
		bool sampEventOnActorStreamIn(int actorid, int forplayerid);
		bool sampEventOnActorStreamOut(int actorid, int forplayerid);
		bool sampEventOnDialogResponse(int playerid, int dialogid, int response, int listitem, const char * inputtext);
		bool sampEventOnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid, int bodypart);
		bool sampEventOnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid, int bodypart);
		bool sampEventOnPlayerGiveDamageActor(int playerid, int damaged_actorid, float amount, int weaponid, int bodypart);
		bool sampEventOnPlayerClickMap(int playerid, float fX, float fY, float fZ);
		bool sampEventOnPlayerClickTextDraw(int playerid, int clickedid);
		bool sampEventOnPlayerClickPlayerTextDraw(int playerid, int playertextid);
		bool sampEventOnIncomingConnection(int playerid, const char * ip_address, int port);
		bool sampEventOnTrailerUpdate(int playerid, int vehicleid);
		bool sampEventOnVehicleSirenStateChange(int playerid, int vehicleid, int newstate);
		bool sampEventOnPlayerClickPlayer(int playerid, int clickedplayerid, int source);
		bool sampEventOnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ);
		bool sampEventOnPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ);
		bool sampEventOnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ);
		bool sampEventOnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float fX, float fY, float fZ);

		bool _impl_OnPlayerEnterRaceCheckpoint(int playerid);
		bool _impl_OnPlayerLeaveRaceCheckpoint(int playerid);

		/////////////////////////////////////////////////////////////////////////////

		/*	Contains default parameters/methods.
		*/
		class Default
		{
		public:			
			/// <summary>
			/// Checks player name validity.
			/// </summary>
			/// <param name="name_">The name.</param>
			/// <returns>
			///   <c>true</c> if valid; otherwise, <c>false</c>.
			/// </returns>
			/// <remarks>
			/// <para>This is only the default method. You can pass other function to Player::setName method.</para>
			/// </remarks>
			static bool	isPlayerNameValid(const std::string_view name_);
		};
	private:
		Clock::duration						m_lastUpdate; /// Stores last server update call (used to determine deltaTime).
	};
}

extern std::unique_ptr<agdk::Server>		g_server;		/// Global pointer to Server
extern std::unique_ptr<agdk::IGameMode>		g_gameMode;		/// Global pointer to Game Mode