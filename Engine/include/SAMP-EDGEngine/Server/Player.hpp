#pragma once

// Base classes:
#include <SAMP-EDGEngine/World/WI3DNode.hpp>
#include <SAMP-EDGEngine/Server/TextDrawOwner.hpp>

// Custom includes:
#include <SAMP-EDGEngine/Server/Weapon.hpp>
#include <SAMP-EDGEngine/World/PersonalObject.hpp>

#include <SAMP-EDGEngine/Core/TaskSystem.hpp>
#include <SAMP-EDGEngine/Core/Color.hpp>
#include <SAMP-EDGEngine/Core/Clock.hpp>
#include <SAMP-EDGEngine/Core/Pointers.hpp>
#include <SAMP-EDGEngine/Core/BasicInterfaces/PlacementTracker.hpp>
#include <SAMP-EDGEngine/Core/TypesAndDefinitions.hpp>
#include <SAMP-EDGEngine/World/Checkpoint.hpp>
#include <SAMP-EDGEngine/World/RaceCheckpoint.hpp>
#include <SAMP-EDGEngine/Server/PlayerTextDraw.hpp>
#include <SAMP-EDGEngine/Server/Dialog.hpp>
#include <SAMP-EDGEngine/Server/Teleport.hpp>


namespace samp_edgengine
{
class RaceCheckpoint;
class Checkpoint;
class Vehicle;
class IGameMode;

/// <summary>
/// Wraps SAMP player data into class.
/// </summary>
class Player
	:
	public std::enable_shared_from_this<Player>,
	public IWI3DNode,
	public TextDrawOwner<PlayerTextDraw>
{
public:
	// Types and aliases
	using IndexType			= Int32;
	using ClassIndexType	= Int32;
	using StateType			= Int32;

	enum class ExistingStatus
	{
		Spawning,
		Spawned,
		Dead,
		SelectingClass,
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
	/// <param name="gameMode_">Reference to GameMode player is managed by.</param>
	/// <param name="index_">Index of the player.</param>
	Player(IGameMode& gameMode_, IndexType const index_);
		
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

	// Dialogs:
	
	/// <summary>
	/// Sets the dialog.
	/// </summary>
	/// <param name="dialog_">The dialog.</param>
	void setDialog(UniquePtr<IDialog> && dialog_);
	
	/// <summary>
	/// Clears the dialog.
	/// </summary>
	void clearDialog();

	/// <summary>
	/// Returns pointer to the dialog or nullptr if dialog is not set.
	/// </summary>
	/// <returns>Pointer to the dialog or nullptr if dialog is not set.</returns>
	IDialog* getDialog() const;

	// Checkpoints:
	
	/// <summary>
	/// Sets the checkpoint streaming on or off.
	/// </summary>
	/// <param name="streamCheckpoints_">if set to <c>true</c> then player has streamed checkpoints.</param>
	void setCheckpointStreaming(bool streamCheckpoints_);
	
	/// <summary>
	/// Sets the race checkpoint streaming.
	/// </summary>
	/// <param name="streamRaceCheckpoints_">if set to <c>true</c> then player has streamed race checkpoints.</param>
	void setRaceCheckpointStreaming(bool streamRaceCheckpoints_);
	
	/// <summary>
	/// Determines whether player has streamed checkpoints.
	/// </summary>
	/// <returns>
	///		<c>true</c> if player has streamed checkpoints; otherwise, <c>false</c>.
	/// </returns>
	bool hasStreamedCheckpoints() const;
	
	/// <summary>
	/// Determines whether player has streamed race checkpoints.
	/// </summary>
	/// <returns>
	///   <c>true</c> if has streamed race checkpoints; otherwise, <c>false</c>.
	/// </returns>
	bool hasStreamedRaceCheckpoints() const;
	
	/// <summary>
	/// Sets the checkpoint.
	/// </summary>
	/// <param name="checkpoint_">The checkpoint.</param>
	void setCheckpoint(Checkpoint const& checkpoint_);
	
	/// <summary>
	/// Sets the race checkpoint.
	/// </summary>
	/// <param name="raceCheckpoint_">The race checkpoint.</param>
	void setRaceCheckpoint(RaceCheckpoint const& raceCheckpoint_);
	
	/// <summary>
	/// Removes the checkpoint.
	/// </summary>
	void removeCheckpoint();
	
	/// <summary>
	/// Removes the race checkpoint.
	/// </summary>
	void removeRaceCheckpoint();
	
	/// <summary>
	/// Determines whether player has checkpoint set.
	/// </summary>
	/// <returns>
	///		<c>true</c> if player has checkpoint set; otherwise, <c>false</c>.
	/// </returns>
	bool hasCheckpointSet() const;
	
	/// <summary>
	/// Determines whether player has race checkpoint set.
	/// </summary>
	/// <returns>
	///   <c>true</c> if player has race checkpoint set; otherwise, <c>false</c>.
	/// </returns>
	bool hasRaceCheckpointSet() const;
	
	/// <summary>
	/// Checks if player intersects with checkpoint.
	/// </summary>
	/// <returns>
	///		<c>true</c> if player intersects with checkpoint; otherwise, <c>false</c>.
	/// </returns>
	bool intersectsWithCheckpoint() const;

	/// <summary>
	/// Checks if player intersects with race checkpoint.
	/// </summary>
	/// <returns>
	///		<c>true</c> if player intersects with race checkpoint; otherwise, <c>false</c>.
	/// </returns>
	bool intersectsWithRaceCheckpoint() const;
	
	/// <summary>
	/// Returns the last checkpoint set.
	/// </summary>
	/// <returns>The last checkpoint set.</returns>
	Checkpoint getLastCheckpoint() const
	{
		return m_checkpoint;
	}

	/// <summary>
	/// Returns the last race checkpoint set.
	/// </summary>
	/// <returns>The last race checkpoint set.</returns>
	RaceCheckpoint getLastRaceCheckpoint() const
	{
		return m_raceCheckpoint;
	}

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
	/// Teleports player to another location.
	/// </summary>
	/// <param name="teleport_">The teleport.</param>
	/// <param name="freezeTime_">Time to freeze the player.</param>
	void teleport(Teleport const &teleport_, Clock::Duration freezeTime_ = {});

	/// <summary>
	/// Sets the player's location.
	/// </summary>
	/// <param name="location_">The location.</param>
	virtual void setLocation(math::Vector3f const &location_) override;
		
	/// <summary>
	/// Sets player's facing angle.
	/// </summary>
	/// <param name="angle_">The angle.</param>
	void setFacingAngle(float const angle_);

	/// <summary>
	/// Sets the player's world.
	/// </summary>
	/// <param name="location_">The world.</param>
	virtual void setWorld(Int32 const world_) override;

	/// <summary>
	/// Sets the player's interior.
	/// </summary>
	/// <param name="location_">The interior.</param>
	virtual void setInterior(Int32 const interior_) override;

	void setCameraLocation(math::Vector3f const & eyeLocation_);
	void setCameraLookAtLocation(math::Vector3f const & lookAtLocation_);

	// Player statistics:

	
	/// <summary>
	/// Adds cash to player.
	/// </summary>
	/// <param name="amount_">The amount of cash to add.</param>
	void addCash(Int32 amount_)
	{
		this->setCash(this->getCash() + amount_);
	}

	/// <summary>
	/// Subtracts cash from player.
	/// </summary>
	/// <param name="amount_">The amount of cash to subtract.</param>
	void subtractCash(Int32 amount_)
	{
		this->setCash(this->getCash() - amount_);
	}

	/// <summary>
	/// Sets player's cash.
	/// </summary>
	/// <param name="cash_">The amount of cash to set</param>
	void setCash(Int32 cash_);
	
	/// <summary>
	/// Adds score to player.
	/// </summary>
	/// <param name="amount_">The amount of score to add.</param>
	void addScore(Int32 amount_)
	{
		this->setScore(this->getCash() + amount_);
	}

	/// <summary>
	/// Subtracts score from player.
	/// </summary>
	/// <param name="amount_">The amount of score to subtract.</param>
	void subtractScore(Int32 amount_)
	{
		this->setScore(this->getCash() - amount_);
	}

	/// <summary>
	/// Sets player's score.
	/// </summary>
	/// <param name="score_">The amount of score to set</param>
	void setScore(Int32 score_);

	// Player condition.

	/// <summary>
	/// Kicks player from the server.
	/// </summary>
	void kick();

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
	void damage(float damage_, bool physical_ = false) // TODO: add proper implementation
	{	
	}

	/// <summary>
	/// Freezes the player for specified amount of time.
	/// </summary>
	/// <param name="freezeDuration_">The freeze duration.</param>
	void freeze(Clock::Duration freezeDuration_);

	/// <summary>
	/// Unfreezes the player.
	/// </summary>
	void unfreeze();

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
	Int32 getVehicleSeat() const;

	/// <summary>
	/// Returns the player's vehicle.
	/// </summary>
	/// <returns>Player's vehicle.</returns>
	Vehicle* getVehicle() const;

	// Weapons:
	
	/// <summary>
	/// Sets weapon set,
	/// </summary>
	/// <param name="weaponSet_">The weapon set.</param>
	void setWeaponSet(WeaponSet const & weaponSet_);

	/// <summary>
	/// Adds the weapon.
	/// </summary>
	/// <param name="weapon_">The weapon.</param>
	void addWeapon(Weapon const weapon_);

	// Player data.

	/// <summary>
	/// Returns IGameMode player is managed by.
	/// </summary>
	/// <returns>IGameMode player is managed by.</returns>
	IGameMode& getGameMode() const noexcept {
		return m_gameMode;
	}

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
	virtual math::Vector3f getLocation() const override;

	/// <summary>
	/// Returns the player world.
	/// </summary>
	/// <returns>Player world.</returns>
	virtual Int32 getWorld() const override;

	/// <summary>
	/// Returns the player interior.
	/// </summary>
	/// <returns>Player interior.</returns>
	virtual Int32 getInterior() const override;

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
	Int32 getScore() const;

	/// <summary>
	/// Returns player's cash.
	/// </summary>
	/// <returns>Player's cash.</returns>
	Int32 getCash() const;

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
	Uint16 getLanguage() const noexcept;

	// Player status.

	/// <summary>
	/// Determines whether this player is spawned.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this player is spawned; otherwise, <c>false</c>.
	/// </returns>
	bool isSpawned() const noexcept;

	/// <summary>
	/// Determines whether this player is selecting character.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this player is selecting character; otherwise, <c>false</c>.
	/// </returns>
	bool isSelectingClass() const noexcept;

	/// <summary>
	/// Determines whether this player is frozen (uncontrollable).
	/// </summary>
	/// <returns>
	///   <c>true</c> if this player is frozen; otherwise, <c>false</c>.
	/// </returns>
	bool isFrozen() const noexcept;

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

	friend class ServerClass;
	friend class MapClass;
	friend class IStreamer;
	friend class PlayerTextDraw;
	friend class IGameMode;
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
	Int32 getClientWorld() const;

	/// <summary>
	/// Returns the client interior.
	/// </summary>
	/// <returns>Client interior.</returns>
	Int32 getClientInterior() const;

	/// <summary>
	/// Returns the client vehicle.
	/// </summary>
	/// <returns></returns>
	Int32 getClientVehicle() const;

private:

	/// <summary>
	/// Sets whether player is inside checkpoint.
	/// </summary>
	/// <param name="inside_">if set to <c>true</c> player is inside checkpoint.</param>
	void setInsideCheckpoint(bool inside_)
	{
		m_insideCheckpoint = inside_;
	}

	/// <summary>
	/// Sets whether player is inside race checkpoint.
	/// </summary>
	/// <param name="inside_">if set to <c>true</c> player is inside race checkpoint.</param>
	void setInsideRaceCheckpoint(bool inside_)
	{
		m_insideRaceCheckpoint = inside_;
	}

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

	IGameMode&			m_gameMode;			/// Reference to IGameMode the player is managed by.

	const IndexType		m_index;			/// Player in-game index.
	std::string			m_name;				/// Player in-game nickname.

	ExistingStatus		m_existingStatus;	/// Determines whether player is spawned, dead or spectating.
		
	// Player statistics.
		
	Int32				m_score;			/// Player's in-game score.
	Int32				m_cash;				/// Player's in-game cash.

	// Player condition.
	float				m_health;			/// Player's in-game health.
	float				m_armour;			/// Player's in-game armour.
	Vehicle*			m_vehicle;			/// Vehicle player sits in.

	Clock::TimePoint 	m_unfreezeTime;
	SharedPtr<Task>		m_unfreezeTask;

	// Player personal settings:
	Uint16				m_language;			/// Player's language.

	// Tracking:
	I3DNodePlacementTracker* m_placementTracker;

	// Dialog:
	UniquePtr<IDialog>	m_dialog;

	// Checkpoint:
	Checkpoint			m_checkpoint;
	RaceCheckpoint		m_raceCheckpoint;
	bool				m_checkpointSet,
						m_raceCheckpointSet,
						m_checkpointStreamingOn,
						m_raceCheckpointStreamingOn;

	bool				m_insideCheckpoint,
						m_insideRaceCheckpoint;

	std::vector< UniquePtr<PersonalObject> > m_personalObjects;
};
}
