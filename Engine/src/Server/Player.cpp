#include SAMPEDGENGINE_PCH

// Custom includes:
#include <SAMP-EDGEngine/Server/Player.hpp>
#include <SAMP-EDGEngine/Server/Server.hpp>
#include <SAMP-EDGEngine/Core/Text/ASCII.hpp>
#include <SAMP-EDGEngine/Server/GameMode.hpp>
#include <SAMP-EDGEngine/Server/ServerDebugLog.hpp>

#include <SAMP-EDGEngine/World/Vehicle.hpp>


namespace samp_edgengine
{

///////////////////////////////////////////////////////////////////////////
Player::Player(IGameMode& gameMode_, IndexType const index_)
	:
	m_gameMode{ gameMode_ },
	m_index{ index_ }, m_existingStatus{ ExistingStatus::Spawning },
	m_language{ 0 },
	m_score{ 0 }, m_cash{ 0 },
	m_health{ 100 + cxHealthBase }, m_armour{ 0 },
	m_placementTracker{ nullptr },
	m_vehicle{ nullptr },
	m_checkpointSet{ false }, m_raceCheckpointSet{ false },
	m_checkpointStreamingOn{ true }, m_raceCheckpointStreamingOn{ true },
	m_insideCheckpoint{ false }, m_insideRaceCheckpoint{ false }
{
	m_name = this->getClientName();
}

///////////////////////////////////////////////////////////////////////////
Player::~Player()
{
	this->unfreeze();

	// Notify streamer to remove every personal object.
	for (auto const & personalObject : m_personalObjects)
		GameMode->streamer->whenObjectLeavesMap(*personalObject);
}

///////////////////////////////////////////////////////////////////////////
void Player::setPlacementTracker(I3DNodePlacementTracker* tracker_)
{
	m_placementTracker = tracker_;
	this->sendPlacementUpdate();
}

///////////////////////////////////////////////////////////////////////////
I3DNodePlacementTracker* Player::getPlacementTracker() const
{
	return m_placementTracker;
}

///////////////////////////////////////////////////////////////////////////
void Player::setDialog(UniquePtr<IDialog>&& dialog_)
{
	// # Assertion note:
	// Use clearDialog() to remove player's dialog.
	assert(dialog_ != nullptr);

	m_dialog = std::forward< UniquePtr<IDialog> >(dialog_);
	m_dialog->setOwner(*this);
	m_dialog->run();
	m_dialog->show();
}

///////////////////////////////////////////////////////////////////////////
void Player::clearDialog()
{
	m_dialog.reset();
}

///////////////////////////////////////////////////////////////////////////
IDialog* Player::getDialog() const
{
	return m_dialog.get();
}

///////////////////////////////////////////////////////////////////////////
void Player::setCheckpointStreaming(bool streamCheckpoints_)
{
	m_checkpointStreamingOn = streamCheckpoints_;
}

///////////////////////////////////////////////////////////////////////////
void Player::setRaceCheckpointStreaming(bool streamRaceCheckpoints_)
{
	m_raceCheckpointStreamingOn = streamRaceCheckpoints_;
}

///////////////////////////////////////////////////////////////////////////
bool Player::hasStreamedCheckpoints() const
{
	return m_checkpointStreamingOn;
}

///////////////////////////////////////////////////////////////////////////
bool Player::hasStreamedRaceCheckpoints() const
{
	return m_raceCheckpointStreamingOn;
}

///////////////////////////////////////////////////////////////////////////
void Player::setCheckpoint(Checkpoint const& checkpoint_)
{
	m_checkpoint	= checkpoint_;
	m_checkpointSet = true;
	const_a loc		= m_checkpoint.getLocation();
	sampgdk_SetPlayerCheckpoint(this->getIndex(), loc.x, loc.y, loc.z, m_checkpoint.getSize());
}

///////////////////////////////////////////////////////////////////////////
void Player::setRaceCheckpoint(RaceCheckpoint const& raceCheckpoint_)
{
	m_raceCheckpoint	= raceCheckpoint_;
	m_raceCheckpointSet = true;
	const_a loc			= m_raceCheckpoint.getLocation();
	const_a lookAt		= m_raceCheckpoint.getLookAt();
	sampgdk_SetPlayerRaceCheckpoint(this->getIndex(), static_cast<Int32>( m_raceCheckpoint.getType() ), loc.x, loc.y, loc.z, lookAt.x, lookAt.y, lookAt.z, m_raceCheckpoint.getSize());
}

///////////////////////////////////////////////////////////////////////////
void Player::removeCheckpoint()
{
	m_checkpointSet = false;
	sampgdk_DisablePlayerCheckpoint(this->getIndex());
}

///////////////////////////////////////////////////////////////////////////
void Player::removeRaceCheckpoint()
{
	m_raceCheckpointSet = false;
	sampgdk_DisablePlayerRaceCheckpoint(this->getIndex());
}

///////////////////////////////////////////////////////////////////////////
bool Player::hasCheckpointSet() const
{
	return m_checkpointSet;
}

///////////////////////////////////////////////////////////////////////////
bool Player::hasRaceCheckpointSet() const
{
	return m_raceCheckpointSet;
}

///////////////////////////////////////////////////////////////////////////
bool Player::intersectsWithCheckpoint() const
{
	if (!m_checkpointSet)
		return false;

	const_a loc						= this->getLocation();
	const_a checkLoc				= m_checkpoint.getLocation();
	const_a radius					= m_checkpoint.getIntersectionRadius();
	math::Vector2f const playerXY	= { loc.x, loc.y };
	math::Vector2f const checkXY	= { checkLoc.x, checkLoc.y };
	return (playerXY.distanceSquared(checkXY) <= (radius * radius) && std::fabs(loc.z - checkLoc.z) <= m_checkpoint.getIntersectionHeight());
}

///////////////////////////////////////////////////////////////////////////
bool Player::intersectsWithRaceCheckpoint() const
{
	if (!m_raceCheckpointSet)
		return false;

	const_a loc						= this->getLocation();
	const_a checkLoc				= m_raceCheckpoint.getLocation();
	const_a radius					= m_raceCheckpoint.getIntersectionRadius();
	math::Vector2f const playerXY	= { loc.x, loc.y };
	math::Vector2f const checkXY	= { checkLoc.x, checkLoc.y };
	return (playerXY.distanceSquared(checkXY) <= (radius * radius) && std::fabs(loc.z - checkLoc.z) <= m_raceCheckpoint.getIntersectionHeight());
}

///////////////////////////////////////////////////////////////////////////
float Player::getClientHealth() const
{
	float health{ 0.f };
	sampgdk_GetPlayerHealth(static_cast< int >(this->getIndex()), &health);
	return health;
}

///////////////////////////////////////////////////////////////////////////
float Player::getClientArmour() const
{
	float armour{ 0.f };
	sampgdk_GetPlayerArmour(static_cast< int >(this->getIndex()), &armour);
	return armour;
}

///////////////////////////////////////////////////////////////////////////
Int32 Player::getClientWorld() const
{
	return sampgdk_GetPlayerVirtualWorld(static_cast< int >(this->getIndex()));
}

///////////////////////////////////////////////////////////////////////////
Int32 Player::getClientInterior() const
{
	return sampgdk_GetPlayerInterior(static_cast< int >(this->getIndex()));
}

///////////////////////////////////////////////////////////////////////////
Int32 Player::getClientVehicle() const
{
	return sampgdk_GetPlayerVehicleID(static_cast< int >(this->getIndex()));
}

///////////////////////////////////////////////////////////////////////////
void Player::setExistingStatus(ExistingStatus status_)
{
	m_existingStatus = status_;
}

///////////////////////////////////////////////////////////////////////////
void Player::setVehicle(Vehicle * const vehicle_) {
	//EDGE_LOG_DEBUG(Info, "Player {0} has vehicle set to {1}", this->getName(), vehicle_ ? vehicle_->getHandle() : Vehicle::InvalidHandle);
	m_vehicle = vehicle_;
}

///////////////////////////////////////////////////////////////////////////
void Player::sendPlacementUpdate()
{
	if ((this->isSpawned() || this->isSelectingClass()) && m_placementTracker)
	{
		m_placementTracker->whenPlacementUpdateReceived(this->getPlacement());
	}
}

///////////////////////////////////////////////////////////////////////////
void Player::sendPlacementUpdate(PlayerPlacement const customPlacement_)
{
	if (this->isSpawned() && m_placementTracker)
	{
		m_placementTracker->whenPlacementUpdateReceived( customPlacement_ );
	}
}

///////////////////////////////////////////////////////////////////////////
math::Vector3f Player::getClientLocation() const
{
	math::Vector3f result;
	sampgdk_GetPlayerPos(static_cast< int >(this->getIndex()), &result.x, &result.y, &result.z);
	return result;
}

///////////////////////////////////////////////////////////////////////////
PersonalObject& Player::finalizePersonalObjectConstruction(UniquePtr<PersonalObject>&& personalObject_)
{
	PersonalObject* objectPtr = personalObject_.get();
	m_personalObjects.push_back(std::forward< UniquePtr<PersonalObject> >(personalObject_));
	GameMode->streamer->whenObjectJoinsMap(*objectPtr);
	return *objectPtr;
}


///////////////////////////////////////////////////////////////////////////
bool Player::removePersonalObject(PersonalObject& personalObject_)
{
	// Search for the specified personal object:
	auto const it = std::find_if(m_personalObjects.begin(), m_personalObjects.end(),
		[&personalObject_](UniquePtr<PersonalObject> const & element_)
		{
			return &personalObject_ == element_.get();
		});
	if (it != m_personalObjects.end())
	{
		// Notify streamer that object has left the map:
		GameMode->streamer->whenObjectLeavesMap(*it->get());

		// Erase the object from the pool.
		m_personalObjects.erase(it);
		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////
bool Player::setName(std::string_view const name_, bool(*isNameValidProc_)(const std::string_view))
{
	// If passed null pointer use the default method.
	if (isNameValidProc_ == nullptr)
		isNameValidProc_ = &ServerClass::Default::isPlayerNameValid;

	if (isNameValidProc_(name_))
	{
		// Store requested name (we are forced to copy the string, since SAMPGDK requires null terminated C-string).
		std::string newName{ name_ };
		if (text::ascii::equal<text::CaseInsensitive>(name_, this->getName()))
		{
			// Store temporarily modified name.
			std::string tempName{ name_ };

			// We need to change name to some `name_`+"_" string, because it is invalid in SAMP
			// to change name from f.e. "FooBar" to "foobar".
			if (tempName.length() < 21)
				tempName += std::string(21 - tempName.length(), '_');

			sampgdk_SetPlayerName(this->getIndex(), tempName.c_str());
			sampgdk_SetPlayerName(this->getIndex(), newName.c_str());
		}
		else
			sampgdk_SetPlayerName(this->getIndex(), newName.c_str());
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
void Player::teleport(Teleport const & teleport_, Clock::Duration freezeTime_)
{
	if(auto vehicle = this->getVehicle())
	{
		bool driver = vehicle->getDriver() == this;

		this->setLocation(teleport_.location + math::Vector3f(0, 0, 0.3f)); // 30cm up to avoid falling through
		this->setFacingAngle(teleport_.facingAngle);

		if (teleport_.world != Teleport::cxNoChange)
			this->setWorld(teleport_.world);
		if (teleport_.interior != Teleport::cxNoChange)
			this->setInterior(teleport_.interior);
			
		if(driver)
		{
			//g_gameMode->sendDebug(String::format(Color::Blue, "Player ", Color::White, this->getName(), Color::Blue, " teleported with vehicle as a driver."));

			auto passengers = vehicle->getPassengers();
			std::map<int, int> seatIds;
			for (auto passenger : passengers)
			{
				if (passenger)
				{
					seatIds[passenger->getIndex()] = sampgdk::GetPlayerVehicleSeat(passenger->getIndex());
					passenger->setLocation(teleport_.location + math::Vector3f(0, 0, 0.3f)); // 30cm up to avoid falling through
					passenger->setFacingAngle(teleport_.facingAngle);
					if (teleport_.world != Teleport::cxNoChange)
						passenger->setWorld(teleport_.world);
					if (teleport_.interior != Teleport::cxNoChange)
						passenger->setInterior(teleport_.interior);
				}
			}


			vehicle->setLocation(teleport_.location + math::Vector3f(0, 0, 0.3f)); // 30cm up to avoid falling through
			vehicle->setFacingAngle(teleport_.facingAngle);
			if (teleport_.world != Teleport::cxNoChange)
				vehicle->setWorld(teleport_.world);
			if (teleport_.interior != Teleport::cxNoChange)
				vehicle->setInterior(teleport_.interior);

			for (auto passenger : passengers)
			{
				passenger->putInVehicle(*vehicle, seatIds[passenger->getIndex()]);
			}
			this->putInVehicle(*vehicle, 0);
		}
		else
		{
			//g_gameMode->sendDebug(String::format(Color::Blue, "Player ", Color::White, this->getName(), Color::Blue, " teleported without vehicle (was passenger)."));
		}
	}
	else
	{
		this->setLocation(teleport_.location + math::Vector3f(0, 0, 0.3f)); // 30cm up to avoid falling through
		this->setFacingAngle(teleport_.facingAngle);
		if (teleport_.world != Teleport::cxNoChange)
			this->setWorld(teleport_.world);
		if (teleport_.interior != Teleport::cxNoChange)
			this->setInterior(teleport_.interior);
		//g_gameMode->sendDebug(String::format(Color::Blue, "Player ", Color::White, this->getName(), Color::Blue, " teleported without vehicle."));
	}

	if (freezeTime_ > chrono::seconds{0})
		this->freeze(freezeTime_);
}

///////////////////////////////////////////////////////////////////////////
void Player::setLocation(math::Vector3f const &location_)
{
	IWI3DNode::setLocation(location_);

	if (m_existingStatus != ExistingStatus::Dead)
		sampgdk_SetPlayerPos(this->getIndex(), location_.x, location_.y, location_.z);

	this->sendPlacementUpdate();
}

///////////////////////////////////////////////////////////////////////////
void Player::setVelocity(math::Vector3f const &velocity_)
{
	sampgdk_SetPlayerVelocity(this->getIndex(), velocity_.x, velocity_.y, velocity_.z);
}

///////////////////////////////////////////////////////////////////////////
void Player::setFacingAngle(float const angle_)
{
	if (m_existingStatus != ExistingStatus::Dead)
		sampgdk_SetPlayerFacingAngle(this->getIndex(), angle_);
}

///////////////////////////////////////////////////////////////////////////
void Player::setWorld(Int32 const world_)
{
	IWI3DNode::setWorld(world_);

	if (m_existingStatus != ExistingStatus::Dead)
		sampgdk_SetPlayerVirtualWorld(this->getIndex(), world_);

	this->sendPlacementUpdate();
}

///////////////////////////////////////////////////////////////////////////
void Player::setInterior(Int32 const interior_)
{
	IWI3DNode::setInterior(interior_);

	if (m_existingStatus != ExistingStatus::Dead)
		sampgdk_SetPlayerInterior(this->getIndex(), interior_);

	this->sendPlacementUpdate();
}

///////////////////////////////////////////////////////////////////////////
void Player::setCameraLocation(math::Vector3f const & eyeLocation_)
{
	sampgdk_SetPlayerCameraPos(this->getIndex(), eyeLocation_.x, eyeLocation_.y, eyeLocation_.z);
}

///////////////////////////////////////////////////////////////////////////
void Player::setCameraBehindPlayer()
{
	sampgdk_SetCameraBehindPlayer(this->getIndex());
}

///////////////////////////////////////////////////////////////////////////
void Player::setCameraLookAtLocation(math::Vector3f const & lookAtLocation_)
{
	sampgdk_SetPlayerCameraLookAt(this->getIndex(), lookAtLocation_.x, lookAtLocation_.y, lookAtLocation_.z, CAMERA_CUT);
}

///////////////////////////////////////////////////////////////////////////
void Player::setCash(Int32 cash_)
{
	m_cash = cash_;
	sampgdk_GivePlayerMoney(this->getIndex(), m_cash - sampgdk_GetPlayerMoney(this->getIndex()));
}

///////////////////////////////////////////////////////////////////////////
void Player::setScore(Int32 score_)
{
	m_score = score_;
	sampgdk_SetPlayerScore(this->getIndex(), m_score);
}

///////////////////////////////////////////////////////////////////////////
void Player::kick()
{
	sampgdk_Kick(this->getIndex());
}

///////////////////////////////////////////////////////////////////////////
void Player::setHealth(float const health_)
{
	m_health = health_ + cxHealthBase;

	if (m_existingStatus != ExistingStatus::Dead)
	{
		// TODO: find better solution.
		if (health_ <= 0.01f)
			sampgdk_SetPlayerHealth(this->getIndex(), 0);
		else
			sampgdk_SetPlayerHealth(this->getIndex(), m_health);
	}
}

///////////////////////////////////////////////////////////////////////////
void Player::setArmor(float const armour_)
{
	m_armour = armour_;

	if (m_existingStatus != ExistingStatus::Dead)
		sampgdk_SetPlayerArmour(this->getIndex(), m_armour);
}

///////////////////////////////////////////////////////////////////////////
void Player::setColor(Color const & color_)
{
	sampgdk_SetPlayerColor(this->getIndex(), color_.toInt32());
}

///////////////////////////////////////////////////////////////////////////
void Player::setSkin(Int32 skin_)
{
	m_skin = skin_;
	if (this->isSpawned()) {
		sampgdk_SetPlayerSkin(this->getIndex(), skin_);
	}
}

///////////////////////////////////////////////////////////////////////////
void Player::damage(float damage_, bool physical_) // TODO: add proper implementation
{
	if (physical_)
	{
		this->setHealth(this->getHealth() - damage_);
	}
	else
	{
		float takeFromAP = std::min(this->getArmour(), damage_);
		this->setArmor(this->getArmour() - takeFromAP);
		if (takeFromAP < damage_)
		{
			this->setHealth(this->getHealth() - (damage_ - takeFromAP));
		}
	}
}

///////////////////////////////////////////////////////////////////////////
void Player::playSound(Int32 soundIndex_, math::Vector3f location_)
{
	sampgdk_PlayerPlaySound(this->getIndex(), soundIndex_, location_.x, location_.y, location_.z);
}

///////////////////////////////////////////////////////////////////////////
void Player::freeze(Clock::Duration freezeDuration_)
{
	m_unfreezeTime = Clock::now() + freezeDuration_;
	
	if (!m_unfreezeTask) {
		m_unfreezeTask = this->getGameMode().tasks.schedule(m_unfreezeTime - Clock::now(),
				[this]() { this->unfreeze(); }
			);
		sampgdk_TogglePlayerControllable(this->getIndex(), false);
	}
	
}

///////////////////////////////////////////////////////////////////////////
void Player::unfreeze()
{
	m_unfreezeTask.reset();
	m_unfreezeTime = Clock::now();
	sampgdk_TogglePlayerControllable(this->getIndex(), true);
}

///////////////////////////////////////////////////////////////////////////
bool Player::putInVehicle(Vehicle& vehicle_, Int32 seatIndex_)
{
	// TODO: confirm that no vehicle has seat index of 6.
	assert(seatIndex_ >= 0 && seatIndex_ <= 5);

	// Cancel if seat is already occupied:
	if (vehicle_.getPassengers()[seatIndex_])
	{
		return false;
	}

	// Kick player from current vehicle:
	this->kickFromVehicle();

	if (sampgdk_PutPlayerInVehicle(this->getIndex(), vehicle_.getHandle(), seatIndex_))
	{
		this->setVehicle(&vehicle_);
		vehicle_.whenPlayerEnters(*this, seatIndex_);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
bool Player::kickFromVehicle()
{
	if (m_vehicle)
	{
		// TODO: It won't work when player is in RC Vehicle.
		// Try using sampgdk_SetPlayerPos instead.
		this->setLocation(this->getClientLocation());
		// sampgdk_RemovePlayerFromVehicle(this->getIndex());
		m_vehicle->whenPlayerExits(*this);
		this->setVehicle(nullptr);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
bool Player::isInVehicle() const
{
	return m_vehicle != nullptr;
}

///////////////////////////////////////////////////////////////////////////
void Player::showMarker()
{
	for(Int32 i = 0; i < sampgdk_GetPlayerPoolSize(); ++i)
		sampgdk_SetPlayerMarkerForPlayer(i, this->getIndex(), this->getColor().toUint32());
}

///////////////////////////////////////////////////////////////////////////
void Player::hideMarker()
{
	for(Int32  i = 0; i < sampgdk_GetPlayerPoolSize(); ++i)
		sampgdk_SetPlayerMarkerForPlayer(i, this->getIndex(), this->getColor().toUint32() & 0xFFFFFF00);
}

///////////////////////////////////////////////////////////////////////////
bool Player::isMarkerVisible() const
{
	return true; // TODO: implement this:
}

///////////////////////////////////////////////////////////////////////////
void Player::showNameTagFor(Player const & player_)
{
	sampgdk::ShowPlayerNameTagForPlayer(player_.getIndex(), this->getIndex(), true);
}

///////////////////////////////////////////////////////////////////////////
void Player::showNameTag()
{
	for(Int32 i = 0; i < sampgdk_GetPlayerPoolSize(); ++i)
		sampgdk::ShowPlayerNameTagForPlayer(i, this->getIndex(), true);
}

///////////////////////////////////////////////////////////////////////////
void Player::hideNameTagFor(Player const & player_)
{
	sampgdk::ShowPlayerNameTagForPlayer(player_.getIndex(), this->getIndex(), false);
}

///////////////////////////////////////////////////////////////////////////
void Player::hideNameTag()
{
	for(Int32 i = 0; i < sampgdk_GetPlayerPoolSize(); ++i)
		sampgdk::ShowPlayerNameTagForPlayer(i, this->getIndex(), true);
}

///////////////////////////////////////////////////////////////////////////
bool Player::hasNameTagShownFor(Player const& player_) const
{
	return true; // TODO: implement this.
}

///////////////////////////////////////////////////////////////////////////
void Player::setWeaponSet(WeaponSet const & weaponSet_)
{
	sampgdk::ResetPlayerWeapons(this->getIndex());
	for (auto &weapon : weaponSet_.getWeapons())
	{
		this->addWeapon(weapon);
	}
}

///////////////////////////////////////////////////////////////////////////
void Player::addWeapon(Weapon const weapon_)
{
	sampgdk_GivePlayerWeapon(this->getIndex(), weapon_.getTypeIndex(), weapon_.getAmmo());
}

///////////////////////////////////////////////////////////////////////////
Player::IndexType Player::getIndex() const noexcept
{
	return m_index;
}

///////////////////////////////////////////////////////////////////////////
std::string Player::getName() const
{
	return m_name;
}

///////////////////////////////////////////////////////////////////////////
std::string Player::getClientName() const
{
	char name[MAX_PLAYER_NAME];
	sampgdk_GetPlayerName(static_cast< int >(this->getIndex()), name, MAX_PLAYER_NAME);
	return std::string{ name };
}

///////////////////////////////////////////////////////////////////////////
math::Vector3f Player::getLocation() const
{
	return (this->isInWorld() ? this->getClientLocation() : IWI3DNode::getLocation());
}

///////////////////////////////////////////////////////////////////////////
math::Vector3f Player::getVelocity() const
{
	math::Vector3f vel;
	sampgdk_GetPlayerVelocity(this->getIndex(), &vel.x, &vel.y, &vel.z);
	return vel;
}

///////////////////////////////////////////////////////////////////////////
Int32 Player::getWorld() const
{
	return (this->isInWorld() ? this->getClientWorld() : IWI3DNode::getWorld());
}

///////////////////////////////////////////////////////////////////////////
Int32 Player::getInterior() const
{
	return (this->isInWorld() ? this->getClientInterior() : IWI3DNode::getInterior());
}

///////////////////////////////////////////////////////////////////////////
math::Meters Player::getDistanceTo(math::Vector3f const location_) const
{
	return math::Meters{ static_cast< math::Meters::ValueType >(this->getLocation().distance(location_)) };
}

///////////////////////////////////////////////////////////////////////////
float Player::getFacingAngle() const
{
	if (this->isInWorld())
	{
		float angle{ 0.f };
		if (sampgdk_GetPlayerFacingAngle(static_cast< int >(this->getIndex()), &angle))
			return angle;
	}
	return 0.f;
}

///////////////////////////////////////////////////////////////////////////
PlayerStatus Player::getInGameStatus() const
{
	return static_cast<PlayerStatus>( sampgdk_GetPlayerState(this->getIndex()) );
}

///////////////////////////////////////////////////////////////////////////
CameraMode Player::getCameraMode() const
{
	return static_cast<CameraMode>( sampgdk_GetPlayerCameraMode(this->getIndex()) );
}

///////////////////////////////////////////////////////////////////////////
PlayerPlacement Player::getPlacement() const
{
	return { this->getLocation(), this->getWorld(), this->getInterior() };
}

///////////////////////////////////////////////////////////////////////////
Int32 Player::getScore() const
{
	return m_score;
}

///////////////////////////////////////////////////////////////////////////
Int32 Player::getCash() const
{
	return m_cash;
}

///////////////////////////////////////////////////////////////////////////
float Player::getHealth() const
{
	return m_health - cxHealthBase;
}

///////////////////////////////////////////////////////////////////////////
float Player::getArmour() const
{
	return m_armour;
}

///////////////////////////////////////////////////////////////////////////
Color Player::getColor() const
{
	return Color{ static_cast< Uint32 >(sampgdk_GetPlayerColor(static_cast<Int32>(this->getIndex()))) };
}

///////////////////////////////////////////////////////////////////////////
Int32 Player::getSkin() const
{
	if (this->isSpawned())
		return sampgdk_GetPlayerSkin(this->getIndex());
	else
		return m_skin;
}

///////////////////////////////////////////////////////////////////////////
Int32 Player::getVehicleSeat() const
{
	return sampgdk_GetPlayerVehicleSeat(static_cast< int >(this->getIndex()));
}

///////////////////////////////////////////////////////////////////////////
Vehicle* Player::getVehicle() const
{
	return m_vehicle;
}

///////////////////////////////////////////////////////////////////////////
Uint16 Player::getLanguage() const noexcept
{
	return m_language;
}

///////////////////////////////////////////////////////////////////////////
bool Player::isSpawned() const noexcept
{
	return m_existingStatus == ExistingStatus::Spawned;
}

///////////////////////////////////////////////////////////////////////////
bool Player::isSelectingClass() const noexcept
{
	return m_existingStatus == ExistingStatus::SelectingClass;
}

///////////////////////////////////////////////////////////////////////////
bool Player::isFrozen() const noexcept
{
	return m_unfreezeTask != nullptr;
}

///////////////////////////////////////////////////////////////////////////
bool Player::isInWorld() const noexcept
{
	return	m_existingStatus == ExistingStatus::Spawned ||
			m_existingStatus == ExistingStatus::Spectating;
}

///////////////////////////////////////////////////////////////////////////
Player::ExistingStatus Player::getExistingStatus() const noexcept
{
	return m_existingStatus;
}

///////////////////////////////////////////////////////////////////////////
bool Player::shouldBeDead() const noexcept
{
	return m_health <= cxHealthBase;
}

///////////////////////////////////////////////////////////////////////////
bool Player::shouldClientBeDead() const
{
	return this->getClientHealth() <= 0;
}

}
