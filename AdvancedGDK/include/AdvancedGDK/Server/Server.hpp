/**
 * Header: Server.hpp
 * Author: Pawe³ Syska aka RazzorFlame.
 * Description:
 * Implements Server behaviour and wraps SAMPGDK callbacks into a class.
**/

#pragma once

// SAMPGDK include:
#include <AdvancedGDK/SampGDK.hpp>

// Custom includes:
#include <AdvancedGDK/Misc/Clock.hpp>

// Standard includes:
#include <memory>
#include <string_view>

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
		void Update();

		bool OnGameModeInit();
		bool OnGameModeExit();
		bool OnPlayerConnect(int playerid);
		bool OnPlayerDisconnect(int playerid, int reason);
		bool OnPlayerSpawn(int playerid);
		bool OnPlayerDeath(int playerid, int killerid, int reason);
		bool OnVehicleSpawn(int vehicleid);
		bool OnVehicleDeath(int vehicleid, int killerid);
		bool OnPlayerText(int playerid, const char * text);
		bool OnPlayerCommandText(int playerid, const char * cmdtext);
		bool OnPlayerRequestClass(int playerid, int classid);
		bool OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger);
		bool OnPlayerExitVehicle(int playerid, int vehicleid);
		bool OnPlayerStateChange(int playerid, int newstate, int oldstate);
		bool OnPlayerEnterCheckpoint(int playerid);
		bool OnPlayerLeaveCheckpoint(int playerid);
		bool OnPlayerEnterRaceCheckpoint(int playerid);
		bool OnPlayerLeaveRaceCheckpoint(int playerid);
		bool OnRconCommand(const char * cmd);
		bool OnPlayerRequestSpawn(int playerid);
		bool OnObjectMoved(int objectid);
		bool OnPlayerObjectMoved(int playerid, int objectid);
		bool OnPlayerPickUpPickup(int playerid, int pickupid);
		bool OnVehicleMod(int playerid, int vehicleid, int componentid);
		bool OnEnterExitModShop(int playerid, int enterexit, int interiorid);
		bool OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid);
		bool OnVehicleRespray(int playerid, int vehicleid, int color1, int color2);
		bool OnVehicleDamageStatusUpdate(int vehicleid, int playerid);
		bool OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z, float vel_x, float vel_y, float vel_z);
		bool OnPlayerSelectedMenuRow(int playerid, int row);
		bool OnPlayerExitedMenu(int playerid);
		bool OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid);
		bool OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys);
		bool OnRconLoginAttempt(const char * ip, const char * password, bool success);
		bool OnPlayerUpdate(int playerid);
		bool OnPlayerStreamIn(int playerid, int forplayerid);
		bool OnPlayerStreamOut(int playerid, int forplayerid);
		bool OnVehicleStreamIn(int vehicleid, int forplayerid);
		bool OnVehicleStreamOut(int vehicleid, int forplayerid);
		bool OnActorStreamIn(int actorid, int forplayerid);
		bool OnActorStreamOut(int actorid, int forplayerid);
		bool OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char * inputtext);
		bool OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid, int bodypart);
		bool OnPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid, int bodypart);
		bool OnPlayerGiveDamageActor(int playerid, int damaged_actorid, float amount, int weaponid, int bodypart);
		bool OnPlayerClickMap(int playerid, float fX, float fY, float fZ);
		bool OnPlayerClickTextDraw(int playerid, int clickedid);
		bool OnPlayerClickPlayerTextDraw(int playerid, int playertextid);
		bool OnIncomingConnection(int playerid, const char * ip_address, int port);
		bool OnTrailerUpdate(int playerid, int vehicleid);
		bool OnVehicleSirenStateChange(int playerid, int vehicleid, int newstate);
		bool OnPlayerClickPlayer(int playerid, int clickedplayerid, int source);
		bool OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ);
		bool OnPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ);
		bool OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ);
		bool OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float fX, float fY, float fZ);

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