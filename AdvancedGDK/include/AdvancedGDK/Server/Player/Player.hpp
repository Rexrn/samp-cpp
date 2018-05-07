#pragma once

// The precompiled header
#include ADVANCEDGDK_PCH

// Custom includes:
#include <AdvancedGDK/Core/MathInc.hpp>
#include <AdvancedGDK/Core/Color.hpp>
#include <AdvancedGDK/Server/Player/Weapon.hpp>

#include <AdvancedGDK/Core/BasicInterfaces/PlacementTracker.hpp>

namespace agdk
{	
class Vehicle;

/// <summary>
/// Class wrapping SAMP player data into class.
/// </summary>
class Player
	:
	public std::enable_shared_from_this<Player>
{
public:		

	// Some constants
	static constexpr float cxHealthBase = 256 * 100.f;
		
	/// <summary>
	/// Initializes a new instance of the <see cref="Player"/> class.
	/// </summary>
	/// <param name="index">Index of the player.</param>
	explicit Player(std::size_t const index_);
		
	/// <summary>
	/// Default constructor (deleted, use explicit index constructor instead).
	/// </summary>
	Player() = delete;

	/// <summary>
	/// Copy onstructor (deleted, use explicit index constructor instead).
	/// </summary>
	Player(Player const &)	= delete;

	/// <summary>
	/// Move constructor (deleted, use explicit index constructor instead).
	/// </summary>
	Player(Player &&)		= delete;		

	// Tracking:	
	/// <summary>
	/// Sets the placement tracker.
	/// </summary>
	/// <param name="tracker_">The tracker.</param>
	void setPlacementTracker(IActorPlacementTracker *tracker_);
	
	/// <summary>
	/// Returns the placement tracker.
	/// </summary>
	/// <returns>Placement tracker</returns>
	IActorPlacementTracker* getPlacementTracker() const;

	// Player data.		

	/// <summary>
	/// Sets player name.
	/// </summary>
	/// <param name="name_">The name.</param>
	/// <returns>
	///   <c>true</c> if succeeded; otherwise, <c>false</c>.
	/// </returns>
	bool setName(std::string_view const name_, bool(*isNameValidProc_)(const std::string_view) = nullptr);

	// Player world transform.

	/// <summary>
	/// Sets the player's location.
	/// </summary>
	/// <param name="location_">The location.</param>
	void setLocation(math::Vector3f const location_);
		
	/// <summary>
	/// Sets player's facing angle.
	/// </summary>
	/// <param name="angle_">The angle.</param>
	void setFacingAngle(float const angle_);

	/// <summary>
	/// Sets the player's world.
	/// </summary>
	/// <param name="location_">The world.</param>
	void setWorld(std::int32_t const world_);

	/// <summary>
	/// Sets the player's interior.
	/// </summary>
	/// <param name="location_">The interior.</param>
	void setInterior(std::int32_t const interior_);
		
	// Player condition.

	/// <summary>
	/// Sets player's health.
	/// </summary>
	/// <param name="health_">The health.</param>
	void setHealth(float const health_);

	/// <summary>
	/// Sets player's armour.
	/// </summary>
	/// <param name="armour_">The armour.</param>
	void setArmour(float const armour_);
		
	/// <summary>
	/// Damages the player.
	/// </summary>
	/// <param name="damage_">The damage count.</param>
	/// <param name="physical_">Indicates whether damage should be applied directly to health.</param>
	void damage(const float damage_, bool const physical_ = false);

	// Weapons:
		
	/// <summary>
	/// Adds the weapon.
	/// </summary>
	/// <param name="weapon_">The weapon.</param>
	void addWeapon(Weapon const weapon_);

	// Player data.

	/// <summary>
	/// Returns player index.
	/// </summary>
	/// <returns>Player index (std::size_t).</returns>
	std::size_t getIndex() const noexcept {
		return m_index;
	}
		
	/// <summary>
	/// Returns player name.
	/// </summary>
	/// <returns>Player name.</returns>
	std::string getName() const {
		return m_name;
	}
		
	/// <summary>
	/// Returns the player client name.
	/// </summary>
	/// <returns>The player client name.</returns>
	std::string getClientName() const {
		char name[MAX_PLAYER_NAME];
		sampgdk_GetPlayerName(static_cast<int>( this->getIndex() ), name, MAX_PLAYER_NAME);
		return std::string{ name };
	}
		
	// Player world transform.

	/// <summary>
	/// Returns the player location.
	/// </summary>
	/// <returns>Player location.</returns>
	math::Vector3f getLocation() const {
		return (this->isSpawned() ? this->getClientLocation() : m_lastLocation);
	}

	/// <summary>
	/// Returns the player world.
	/// </summary>
	/// <returns>Player world.</returns>
	std::int32_t getWorld() const {
		return (this->isSpawned() ? this->getClientWorld() : 0);
	}
		
	/// <summary>
	/// Returns the player interior.
	/// </summary>
	/// <returns>Player interior.</returns>
	std::int32_t getInterior() const {
		return (this->isSpawned() ? this->getClientInterior() : 0);
	}
				
	/// <summary>
	/// Returns the distance to specified location.
	/// </summary>
	/// <param name="location_">The location.</param>
	/// <returns>Distance to specified location.</returns>
	math::Meters getDistanceTo(math::Vector3f const location_) const {
		return math::Meters{ static_cast<math::Meters::ValueType>(this->getLocation().distance(location_)) };
	}
		
	/// <summary>
	/// Returns player facing angle.
	/// </summary>
	/// <returns>Player facing angle.</returns>
	float getFacingAngle() const
	{
		if (this->isSpawned())
		{
			float angle{ 0.f };
			if (sampgdk_GetPlayerFacingAngle(static_cast<int>( this->getIndex() ), &angle))
				return angle;
		}
		return 0.f;
	}
	
	/// <summary>
	/// Returns player's placement.
	/// </summary>
	/// <returns>Player's placement.</returns>
	PlayerPlacement getPlacement() const {
		return { this->getLocation(), this->getWorld(), this->getInterior() };
	}

	// Player statistics.
		
	/// <summary>
	/// Returns player's score.
	/// </summary>
	/// <returns>Player's score.</returns>
	std::int32_t getScore() const {
		return m_score;
	}

	/// <summary>
	/// Returns player's cash.
	/// </summary>
	/// <returns>Player's cash.</returns>
	std::int32_t getCash() const {
		return m_cash;
	}
				
	// Player condition.

	/// <summary>
	/// Returns player's health.
	/// </summary>
	/// <returns>Player's health</returns>
	float getHealth() const {
		return m_health - cxHealthBase;
	}

	/// <summary>
	/// Returns player's armour.
	/// </summary>
	/// <returns>Player's armour</returns>
	float getArmour() const {
		return m_armour;
	}
		
	/// <summary>
	/// Returns player's (client) color.
	/// </summary>
	/// <returns>Player's color</returns>
	Color getColor() const {
		return Color{ static_cast<std::uint32_t>( sampgdk_GetPlayerColor( static_cast<int>( this->getIndex() ) ) ) };
	}
		
	/// <summary>
	/// Returns the player's (client) vehicle seat.
	/// </summary>
	/// <returns></returns>
	std::int32_t getVehicleSeat() const {
		return sampgdk_GetPlayerVehicleSeat( static_cast<int>( this->getIndex() ) );
	}
		
	/// <summary>
	/// Returns the player's vehicle.
	/// </summary>
	/// <returns>Player's vehicle.</returns>
	Vehicle* getVehicle() const {
		return m_vehicle;
	}

	// Player personal settings:
		
	/// <summary>
	/// Returns player language.
	/// </summary>
	/// <returns>Player's language</returns>
	std::uint16_t getLanguage() const noexcept {
		return m_language;
	}

	// Player status.

	/// <summary>
	/// Determines whether this player is spawned.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this player is spawned; otherwise, <c>false</c>.
	/// </returns>
	bool isSpawned() const noexcept {
		return true;// TODO: uncomment// m_spawned;
	}
				
	/// <summary>
	/// Determines whether this player is dead.
	/// </summary>
	/// <returns>
	///   <c>true</c> if player is dead; otherwise, <c>false</c>.
	/// </returns>
	bool isDead() const noexcept {
		return m_health <= cxHealthBase;
	}

	/// <summary>
	/// Determines whether client is dead.
	/// </summary>
	/// <returns>
	///   <c>true</c> if client is dead; otherwise, <c>false</c>.
	/// </returns>
	bool isClientDead() const {
		return this->getClientHealth() <= 0;
	}

	// Vehicle pool must access `getClientVehicle` method and `setVehicle`.
	friend class Server;
	friend class VehiclePool;
protected:
				
	/// <summary>
	/// Returns the client health.
	/// </summary>
	/// <returns>Client health.</returns>
	float getClientHealth() const
	{
		float health{ 0.f };
		sampgdk_GetPlayerHealth( static_cast<int>( this->getIndex() ), &health);
		return health;
	}

	/// <summary>
	/// Returns the client armour.
	/// </summary>
	/// <returns>Client armour.</returns>
	float getClientArmour() const
	{
		float armour{ 0.f };
		sampgdk_GetPlayerArmour(static_cast<int>( this->getIndex() ), &armour);
		return armour;
	}

	/// <summary>
	/// Returns the client world.
	/// </summary>
	/// <returns>Client world.</returns>
	std::int32_t getClientWorld() const {
		return sampgdk_GetPlayerVirtualWorld(static_cast<int>( this->getIndex() ));
	}
		
	/// <summary>
	/// Returns the client interior.
	/// </summary>
	/// <returns>Client interior.</returns>
	std::int32_t getClientInterior() const {
		return sampgdk_GetPlayerInterior(static_cast<int>( this->getIndex() ));
	}

	/// <summary>
	/// Returns the client vehicle.
	/// </summary>
	/// <returns></returns>
	std::int32_t getClientVehicle() const {
		return sampgdk_GetPlayerVehicleID(static_cast<int>( this->getIndex() ));
	}

private:
		
	// Tracking:	
	/// <summary>
	/// Sends the placement update to the tracker.
	/// </summary>
	void sendPlacementUpdate();

	/// <summary>
	/// Sets the player vehicle. It just sets pointer to it.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	void setVehicle(Vehicle * const vehicle_) {
		m_vehicle = vehicle_;
	}

	/// <summary>
	/// Returns the client location.
	/// </summary>
	/// <returns>Client location.</returns>
	/// <remarks>
	/// <para>This function is not accurate when player is not spawned, therefore you are forced to use <see cref="Player::getLocation"/>.</para>
	/// </remarks>
	math::Vector3f getClientLocation() const {
		math::Vector3f result;
		sampgdk_GetPlayerPos(static_cast<int>( this->getIndex() ), &result.x, &result.y, &result.z);
		return result;
	}

	const std::size_t	m_index;			/// Player in-game index.
	std::string			m_name;				/// Player in-game nickname.

	bool				m_spawned;			/// Determines whether player is spawned.
	math::Vector3f		m_lastLocation;		/// Last set location.
		
	// Player statistics.
		
	std::int32_t		m_score;			/// Player's in-game score.
	std::int32_t		m_cash;				/// Player's in-game cash.

	// Player condition.
	float				m_health;			/// Player's in-game health.
	float				m_armour;			/// Player's in-game armour.
	Vehicle*			m_vehicle;			/// Vehicle player sits in.

	// Player personal settings:
	std::uint16_t		m_language;			/// Player's language.

	// Tracking:
	IActorPlacementTracker* m_placementTracker;
};
}