// File description:
// Implements Server behaviour and wraps SAMPGDK callbacks into a class.


#pragma once

// Precompiled header:
#include ADVANCEDGDK_PCH

// Custom includes:
#include <AdvancedGDK/Core/Events.hpp>
#include <AdvancedGDK/Core/Clock.hpp>
#include <AdvancedGDK/Server/Player/Player.hpp>
#include <AdvancedGDK/Server/Player/PlayerPool.hpp>
#include <AdvancedGDK/Server/Player/Weapon.hpp>
#include <AdvancedGDK/World/Vehicle/Vehicle.hpp>


namespace agdk
{
	// Forward declarations
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
		
	private:
		struct SampEvents {
			void onUpdate();
			bool onGameModeInit();
			bool onGameModeExit();
			bool onPlayerConnect(int playerid);
			bool onPlayerDisconnect(int playerid, int reason);
			bool onPlayerSpawn(int playerid);
			bool onPlayerDeath(int playerid, int killerid, int reason);
			bool onVehicleSpawn(int vehicleid);
			bool onVehicleDeath(int vehicleid, int killerid);
			bool onPlayerText(int playerid, const char * text);
			bool onPlayerCommandText(int playerid, const char * cmdtext);
			bool onPlayerRequestClass(int playerid, int classid);
			bool onPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger);
			bool onPlayerExitVehicle(int playerid, int vehicleid);
			bool onPlayerStateChange(int playerid, int newstate, int oldstate);
			bool onPlayerEnterCheckpoint(int playerid);
			bool onPlayerLeaveCheckpoint(int playerid);
			bool onPlayerEnterRaceCheckpoint(int playerid);
			bool onPlayerLeaveRaceCheckpoint(int playerid);
			bool onRconCommand(const char * cmd);
			bool onPlayerRequestSpawn(int playerid);
			bool onObjectMoved(int objectid);
			bool onPlayerObjectMoved(int playerid, int objectid);
			bool onPlayerPickUpPickup(int playerid, int pickupid);
			bool onVehicleMod(int playerid, int vehicleid, int componentid);
			bool onEnterExitModShop(int playerid, int enterexit, int interiorid);
			bool onVehiclePaintjob(int playerid, int vehicleid, int paintjobid);
			bool onVehicleRespray(int playerid, int vehicleid, int color1, int color2);
			bool onVehicleDamageStatusUpdate(int vehicleid, int playerid);
			bool onUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z, float vel_x, float vel_y, float vel_z);
			bool onPlayerSelectedMenuRow(int playerid, int row);
			bool onPlayerExitedMenu(int playerid);
			bool onPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid);
			bool onPlayerKeyStateChange(int playerid, int newkeys, int oldkeys);
			bool onRconLoginAttempt(const char * ip, const char * password, bool success);
			bool onPlayerUpdate(int playerid);
			bool onPlayerStreamIn(int playerid, int forplayerid);
			bool onPlayerStreamOut(int playerid, int forplayerid);
			bool onVehicleStreamIn(int vehicleid, int forplayerid);
			bool onVehicleStreamOut(int vehicleid, int forplayerid);
			bool onActorStreamIn(int actorid, int forplayerid);
			bool onActorStreamOut(int actorid, int forplayerid);
			bool onDialogResponse(int playerid, int dialogid, int response, int listitem, const char * inputtext);
			bool onPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid, int bodypart);
			bool onPlayerGiveDamage(int playerid, int damagedid, float amount, int weaponid, int bodypart);
			bool onPlayerGiveDamageActor(int playerid, int damaged_actorid, float amount, int weaponid, int bodypart);
			bool onPlayerClickMap(int playerid, float fX, float fY, float fZ);
			bool onPlayerClickTextDraw(int playerid, int clickedid);
			bool onPlayerClickPlayerTextDraw(int playerid, int playertextid);
			bool onIncomingConnection(int playerid, const char * ip_address, int port);
			bool onTrailerUpdate(int playerid, int vehicleid);
			bool onVehicleSirenStateChange(int playerid, int vehicleid, int newstate);
			bool onPlayerClickPlayer(int playerid, int clickedplayerid, int source);
			bool onPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ);
			bool onPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ);
			bool onPlayerSelectObject(int playerid, int type, int objectid, int modelid, float fX, float fY, float fZ);
			bool onPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float fX, float fY, float fZ);

			bool _impl_OnPlayerEnterRaceCheckpoint(int playerid);
			bool _impl_OnPlayerLeaveRaceCheckpoint(int playerid);
		};

		struct Events {
			EventDispatcher<Clock::TimePoint const>							serverUpdates;
			EventDispatcher<>												gameModeInits;
			EventDispatcher<>												gameModeExits;
			EventDispatcher<Player &>										playerConnects;
			EventDispatcher<Player &>										playerDisconnects;
			EventDispatcher<Player &>										playerSpawns;
			EventDispatcher<Player &, Player *, Weapon::Type>				playerDies;
			EventDispatcher<Vehicle &>										vehicleSpawns;
			EventDispatcher<Vehicle &, Player *>							vehicleDies;
			EventDispatcher<Player &, std::string const&>					playerSendsText;
			EventDispatcher<Player &, std::string const&>					playerSendsCommandText;

			/*void onUpdate();
			bool onGameModeInit();
			bool onGameModeExit();
			bool onPlayerConnect(int playerid);
			bool onPlayerDisconnect(int playerid, int reason);
			bool onPlayerSpawn(int playerid);
			bool onPlayerDeath(int playerid, int killerid, int reason);
			bool onVehicleSpawn(int vehicleid);
			bool onVehicleDeath(int vehicleid, int killerid);
			bool onPlayerText(int playerid, const char * text);
			bool onPlayerCommandText(int playerid, const char * cmdtext);
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
			///   <c>true</c> if valid; otherwise, <c>false</c>.
			/// </returns>
			/// <remarks>
			/// <para>This is only the default method. You can pass other function to Player::setName method.</para>
			/// </remarks>
			static bool	isPlayerNameValid(const std::string_view name_);
		};

		SampEvents							sampEvents;
		Events								events;
	private:
		Clock::TimePoint					m_lastUpdate; /// Stores last server update call (used to determine deltaTime).
	};
}

extern std::unique_ptr<agdk::Server>		g_server;		/// Global pointer to Server
extern std::unique_ptr<agdk::IGameMode>		g_gameMode;		/// Global pointer to Game Mode