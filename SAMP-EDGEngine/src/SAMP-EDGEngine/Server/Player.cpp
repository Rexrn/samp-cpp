#include "SAMP-EDGEnginePCH.hpp" // PCH

// Custom includes:
#include <SAMP-EDGEngine/Server/Player.hpp>
#include <SAMP-EDGEngine/Server/Server.hpp>
#include <SAMP-EDGEngine/Core/Text/ASCII.hpp>
#include <SAMP-EDGEngine/Server/GameMode.hpp>
#include <SAMP-EDGEngine/World/Vehicle.hpp>

namespace agdk
{

///////////////////////////////////////////////////////////////////////////
Player::Player(IndexType const index_)
	:
	m_index{ index_ }, m_existingStatus{ ExistingStatus::Spawning },
	m_score{ 0 }, m_cash{ 0 },
	m_health{ 100 }, m_armour{ 0 },
	m_lastWorld{ 0 }, m_lastInterior{ 0 },
	m_placementTracker{ nullptr },
	m_vehicle{ nullptr }
{
	m_name = this->getClientName();
}

///////////////////////////////////////////////////////////////////////////
Player::~Player()
{
	// Notify streamer to remove every personal object.
	for (auto const & personalObject : m_personalObjects)
		GameMode->Streamer->whenObjectLeavesMap(*personalObject);
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
std::int32_t Player::getClientWorld() const
{
	return sampgdk_GetPlayerVirtualWorld(static_cast< int >(this->getIndex()));
}

///////////////////////////////////////////////////////////////////////////
std::int32_t Player::getClientInterior() const
{
	return sampgdk_GetPlayerInterior(static_cast< int >(this->getIndex()));
}

///////////////////////////////////////////////////////////////////////////
std::int32_t Player::getClientVehicle() const
{
	return sampgdk_GetPlayerVehicleID(static_cast< int >(this->getIndex()));
}

///////////////////////////////////////////////////////////////////////////
void Player::setExistingStatus(ExistingStatus status_)
{
	m_existingStatus = status_;
}

///////////////////////////////////////////////////////////////////////////
void Player::sendPlacementUpdate()
{
	if (this->isSpawned() && m_placementTracker)
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
	GameMode->Streamer->whenObjectJoinsMap(*objectPtr);
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
		GameMode->Streamer->whenObjectLeavesMap(*it->get());

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
void Player::setLocation(math::Vector3f const location_)
{
	m_lastLocation = location_;

	if (m_existingStatus != ExistingStatus::Dead)
		sampgdk_SetPlayerPos(this->getIndex(), location_.x, location_.y, location_.z);

	this->sendPlacementUpdate();
}

///////////////////////////////////////////////////////////////////////////
void Player::setFacingAngle(float const angle_)
{
	if (m_existingStatus != ExistingStatus::Dead)
		sampgdk_SetPlayerFacingAngle(this->getIndex(), angle_);
}

///////////////////////////////////////////////////////////////////////////
void Player::setWorld(std::int32_t const world_)
{
	m_lastWorld = world_;

	if (m_existingStatus != ExistingStatus::Dead)
		sampgdk_SetPlayerVirtualWorld(this->getIndex(), world_);

	this->sendPlacementUpdate();
}

///////////////////////////////////////////////////////////////////////////
void Player::setInterior(std::int32_t const interior_)
{
	m_lastInterior = interior_;

	if (m_existingStatus != ExistingStatus::Dead)
		sampgdk_SetPlayerInterior(this->getIndex(), interior_);
	this->sendPlacementUpdate();
}

///////////////////////////////////////////////////////////////////////////
void Player::setHealth(float const health_)
{
	m_health = health_ + cxHealthBase;
	if (m_existingStatus != ExistingStatus::Dead)
		sampgdk_SetPlayerHealth(this->getIndex(), m_health);
}

///////////////////////////////////////////////////////////////////////////
void Player::setArmour(float const armour_)
{
	m_armour = armour_;
	if (m_existingStatus != ExistingStatus::Dead)
		sampgdk_SetPlayerArmour(this->getIndex(), m_armour);
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
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
bool Player::kickFromVehicle()
{
	if (this->isInVehicle())
	{
		// TODO: It won't work when player is in RC Vehicle.
		// Try using sampgdk_SetPlayerPos instead.
		sampgdk_RemovePlayerFromVehicle(this->getIndex());
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
	return (this->isInWorld() ? this->getClientLocation() : m_lastLocation);
}

///////////////////////////////////////////////////////////////////////////
std::int32_t Player::getWorld() const
{
	return (this->isInWorld() ? this->getClientWorld() : m_lastWorld);
}

///////////////////////////////////////////////////////////////////////////
std::int32_t Player::getInterior() const
{
	return (this->isInWorld() ? this->getClientInterior() : m_lastInterior);
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
PlayerPlacement Player::getPlacement() const
{
	return { this->getLocation(), this->getWorld(), this->getInterior() };
}

///////////////////////////////////////////////////////////////////////////
std::int32_t Player::getScore() const
{
	return m_score;
}

///////////////////////////////////////////////////////////////////////////
std::int32_t Player::getCash() const
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
	return Color{ static_cast< std::uint32_t >(sampgdk_GetPlayerColor(static_cast< int >(this->getIndex()))) };
}

///////////////////////////////////////////////////////////////////////////
std::int32_t Player::getVehicleSeat() const
{
	return sampgdk_GetPlayerVehicleSeat(static_cast< int >(this->getIndex()));
}

///////////////////////////////////////////////////////////////////////////
Vehicle* Player::getVehicle() const
{
	return m_vehicle;
}

///////////////////////////////////////////////////////////////////////////
std::uint16_t Player::getLanguage() const noexcept
{
	return m_language;
}

///////////////////////////////////////////////////////////////////////////
bool Player::isSpawned() const noexcept
{
	return m_existingStatus == ExistingStatus::Spawned;
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
