#pragma once

// The precompiled header
#include ADVANCEDGDK_PCH

// Custom includes:
#include <AdvancedGDK/Server/Weapon.hpp>
#include <AdvancedGDK/World/PersonalObject.hpp>

#include <AdvancedGDK/Core/Color.hpp>
#include <AdvancedGDK/Core/Pointers.hpp>
#include <AdvancedGDK/Core/BasicInterfaces/PlacementTracker.hpp>
#include <AdvancedGDK/Core/TypesAndDefinitions.hpp>


namespace agdk
{	
class Vehicle;

/// <summary>
/// Wraps SAMP player data into class.
/// </summary>
class Player
	:
	public std::enable_shared_from_this<Player>
{
public:
	// Types and aliases
	using IndexType			= int;
	using ClassIndexType	= int;
	using StateType			= int;

	enum class ExistingStatus
	{
		Spawning,
		Spawned,
		Dead,
		Spectating
	};

	enum class BodyPart : Int32
	{
		Torso		= 3,
		Groin		= 4,
		LeftArm		= 5,
		RightArm	= 6,
		LeftLeg		= 7,
		RightLeg	= 8,
		Head		= 9
	};

	enum class DisconnectReason : Int32
	{
		Crash		= 0,
		Quit		= 1,
		Kick		= 2,
		Timeout		= Crash,	// Timeout and Crash are indistinguishable from SAMP perspective
		Ban			= Kick		// Kick and Ban are indistinguishable from SAMP perspective
	};

	// Some constants
	static constexpr IndexType	InvalidIndex = INVALID_PLAYER_ID;
	static constexpr float		cxHealthBase = 256 * 100.f;
		
	/// <summary>
	/// Initializes a new instance of the <see cref="Player"/> class.
	/// </summary>
	/// <param name="index">Index of the player.</param>
	explicit Player(IndexType const index_);
		
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
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Player"/> class.
	/// </summary>
	~Player();

	// Tracking:	
	/// <summary>
	/// Sets the placement tracker.
	/// </summary>
	/// <param name="tracker_">The tracker.</param>
	void setPlacementTracker(I3DNodePlacementTracker *tracker_);
	
	/// <summary>
	/// Returns the placement tracker.
	/// </summary>
	/// <returns>Placement tracker</returns>
	I3DNodePlacementTracker* getPlacementTracker() const;

	// Personal object:

	/// <summary>
	/// Constructs personal object and returns reference to it.
	/// </summary>
	/// <param name="args_">The construction params.</param>
	/// <returns>Reference to the constructed object.</returns>
	template <typename... TArgTypes>
	PersonalObject& constructPersonalObject(TArgTypes&&...args_)
	{
		return this->finalizePersonalObjectConstruction(this->beginPersonalObjectConstruction(std::forward<TArgTypes>(args_)...));
	}

	/// <summary>
	/// Begins construction of the personal object.
	/// </summary>
	/// <param name="args_">The construction params.</param>
	/// <returns>The only owning pointer to the constructed thing.</returns>
	template <typename... TArgTypes>
	UniquePtr<PersonalObject> beginPersonalObjectConstruction(TArgTypes&&...args_)
	{
		return std::make_unique<PersonalObject>( *this, std::forward<TArgTypes>(args_)... );
	}

	/// <summary>
	/// Finalizes the personal object construction - adds it to the pool.
	/// </summary>
	/// <param name="personalObject_">The only owning pointer to vehicle.</param>
	/// <returns>Reference to created vehicle.</returns>
	PersonalObject& finalizePersonalObjectConstruction(UniquePtr< PersonalObject > && personalObject_);
	
	/// <summary>
	/// Removes the personal object.
	/// </summary>
	/// <param name="personalobject_">The personalobject.</param>
	/// <returns>
	///		<c>true</c> if successfully removed; otherwise, <c>false</c>.
	/// </returns>
	bool removePersonalObject(PersonalObject & personalobject_);

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
	void damage(const float damage_, bool const physical_ = false) // TODO: add proper implementation
	{	
	}

	/// <summary>
	/// Puts player inside the vehicle.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	/// <param name="seatIndex_">Index of the seat (0 = driver).</param>
	/// <returns>
	///		<c>true</c> if player was put successfully; otherwise, <c>false</c>.
	/// </returns>
	bool putInVehicle(Vehicle & vehicle_, Int32 seatIndex_);
	
	/// <summary>
	/// Kicks player from current vehicle.
	/// </summary>
	/// <returns>
	///		<c>true</c> if player was in vehicle and was kicked; otherwise, <c>false</c>.
	/// </returns>
	bool kickFromVehicle();
	
	/// <summary>
	/// Determines whether player is in vehicle.
	/// </summary>
	/// <returns>
	///		<c>true</c> if player is in vehicle; otherwise, <c>false</c>.
	/// </returns>
	bool isInVehicle() const;

	/// <summary>
	/// Returns the player's (client) vehicle seat.
	/// </summary>
	/// <returns></returns>
	std::int32_t getVehicleSeat() const;

	/// <summary>
	/// Returns the player's vehicle.
	/// </summary>
	/// <returns>Player's vehicle.</returns>
	Vehicle* getVehicle() const;

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
	IndexType getIndex() const noexcept;

	/// <summary>
	/// Returns player name.
	/// </summary>
	/// <returns>Player name.</returns>
	std::string getName() const;

	/// <summary>
	/// Returns the player client name.
	/// </summary>
	/// <returns>The player client name.</returns>
	std::string getClientName() const;

	// Player world transform.

	/// <summary>
	/// Returns the player location.
	/// </summary>
	/// <returns>Player location.</returns>
	math::Vector3f getLocation() const;

	/// <summary>
	/// Returns the player world.
	/// </summary>
	/// <returns>Player world.</returns>
	std::int32_t getWorld() const;

	/// <summary>
	/// Returns the player interior.
	/// </summary>
	/// <returns>Player interior.</returns>
	std::int32_t getInterior() const;

	/// <summary>
	/// Returns the distance to specified location.
	/// </summary>
	/// <param name="location_">The location.</param>
	/// <returns>Distance to specified location.</returns>
	math::Meters getDistanceTo(math::Vector3f const location_) const;

	/// <summary>
	/// Returns player facing angle.
	/// </summary>
	/// <returns>Player facing angle.</returns>
	float getFacingAngle() const;

	/// <summary>
	/// Returns player's placement.
	/// </summary>
	/// <returns>Player's placement.</returns>
	PlayerPlacement getPlacement() const;

	// Player statistics.
		
	/// <summary>
	/// Returns player's score.
	/// </summary>
	/// <returns>Player's score.</returns>
	std::int32_t getScore() const;

	/// <summary>
	/// Returns player's cash.
	/// </summary>
	/// <returns>Player's cash.</returns>
	std::int32_t getCash() const;

	// Player condition.

	/// <summary>
	/// Returns player's health.
	/// </summary>
	/// <returns>Player's health</returns>
	float getHealth() const;

	/// <summary>
	/// Returns player's armour.
	/// </summary>
	/// <returns>Player's armour</returns>
	float getArmour() const;

	/// <summary>
	/// Returns player's (client) color.
	/// </summary>
	/// <returns>Player's color</returns>
	Color getColor() const;

	// Player personal settings:
		
	/// <summary>
	/// Returns player language.
	/// </summary>
	/// <returns>Player's language</returns>
	std::uint16_t getLanguage() const noexcept;

	// Player status.

	/// <summary>
	/// Determines whether this player is spawned.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this player is spawned; otherwise, <c>false</c>.
	/// </returns>
	bool isSpawned() const noexcept;

	/// <summary>
	/// Determines whether this player is in world (is spawned or is spectating).
	/// </summary>
	/// <returns>
	///   <c>true</c> if this player is in world; otherwise, <c>false</c>.
	/// </returns>
	bool isInWorld() const noexcept;
	
	/// <summary>
	/// Returns player's existing status.
	/// </summary>
	/// <returns></returns>
	ExistingStatus getExistingStatus() const noexcept;

	/// <summary>
	/// Determines whether this player is dead.
	/// </summary>
	/// <returns>
	///   <c>true</c> if player is dead; otherwise, <c>false</c>.
	/// </returns>
	bool shouldBeDead() const noexcept;

	/// <summary>
	/// Determines whether client is dead.
	/// </summary>
	/// <returns>
	///   <c>true</c> if client is dead; otherwise, <c>false</c>.
	/// </returns>
	bool shouldClientBeDead() const;

	// Tracking:
	/// <summary>
	/// Sends the placement update to the tracker.
	/// </summary>
	void sendPlacementUpdate();

	/// <summary>
	/// Sends the placement update to the tracker.
	/// </summary>
	void sendPlacementUpdate(PlayerPlacement const customPlacement_);

	// Vehicle pool must access `getClientVehicle` method and `setVehicle`.
	friend class ServerClass;
	friend class MapClass;
	friend class IStreamer;
protected:
				
	/// <summary>
	/// Returns the client health.
	/// </summary>
	/// <returns>Client health.</returns>
	float getClientHealth() const;

	/// <summary>
	/// Returns the client armour.
	/// </summary>
	/// <returns>Client armour.</returns>
	float getClientArmour() const;

	/// <summary>
	/// Returns the client world.
	/// </summary>
	/// <returns>Client world.</returns>
	std::int32_t getClientWorld() const;

	/// <summary>
	/// Returns the client interior.
	/// </summary>
	/// <returns>Client interior.</returns>
	std::int32_t getClientInterior() const;

	/// <summary>
	/// Returns the client vehicle.
	/// </summary>
	/// <returns></returns>
	std::int32_t getClientVehicle() const;

private:
			
	/// <summary>
	/// Sets whether the player is spawned or not.
	/// </summary>
	/// <param name="spawned_">spawned if set to <c>true</c>.</param>
	void setExistingStatus(ExistingStatus status_);

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
	math::Vector3f getClientLocation() const;

	const IndexType		m_index;			/// Player in-game index.
	std::string			m_name;				/// Player in-game nickname.

	ExistingStatus		m_existingStatus;	/// Determines whether player is spawned, dead or spectating.
	math::Vector3f		m_lastLocation;		/// Last set location.
	Int32				m_lastInterior;		/// Last set interior
	Int32				m_lastWorld;		/// Last set world
		
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
	I3DNodePlacementTracker* m_placementTracker;

	std::vector< UniquePtr<PersonalObject> > m_personalObjects;
};
}
