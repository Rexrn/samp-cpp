#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/Vehicle.hpp>
#include <AdvancedGDK/Server/Server.hpp>
#include <AdvancedGDK/Server/GameMode.hpp>
#include <AdvancedGDK/Core/Text/ASCII.hpp>
#include <AdvancedGDK/Core/Clock.hpp>

namespace agdk
{

/////////////////////////////////////////////////////////////////////////////////
Vehicle::Vehicle()
	:
	m_handle{ InvalidHandle },
	m_modelIndex{ -1 },
	m_facingAngle{ 0 },
	m_firstColor{ math::random::generate<Int32>(0, 255) },
	m_secondColor{ math::random::generate(0, 255) },
	m_passengers{ nullptr },
	m_placementTracker{ nullptr }
{
	// Keep vehicle in memory for at least 1 minute after creation
	m_latestUsage = Clock::now() + chrono::seconds(60);
}

/////////////////////////////////////////////////////////////////////////////////
Vehicle::~Vehicle()
{
	if (this->isSpawned())
		this->despawn();
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::respawn()
{
	if (this->isSpawned()) {
		this->despawn();
		this->spawn();
	}
	else
		this->spawn();
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::repair()
{
	if (this->isSpawned()) {
		sampgdk_RepairVehicle(this->getHandle());
		this->setHealth(1000.f);
	}
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::setHealth(float health_)
{
	if (this->isSpawned())
		sampgdk_SetVehicleHealth(this->getHandle(), health_);
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::setWorld(Int32 world_)
{
	Super::setWorld(world_);

	if (this->isSpawned())
		sampgdk_SetVehicleVirtualWorld(this->getHandle(), m_world);

	this->sendPlacementUpdate();
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::setInterior(std::int32_t const interior_)
{
	m_interior = interior_;
	if (this->isSpawned())
		sampgdk_LinkVehicleToInterior(this->getHandle(), m_interior);

	this->sendPlacementUpdate();
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::setLocation(math::Vector3f const & location_)
{
	m_location = location_;
	if (this->isSpawned())
		sampgdk_SetVehiclePos(this->getHandle(), m_location.x, m_location.y, m_location.z);

	this->sendPlacementUpdate();
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::setFacingAngle(float const angle_)
{
	m_facingAngle = angle_;
	if (this->isSpawned())
		sampgdk_SetVehicleZAngle(this->getHandle(), m_facingAngle);
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::setSpeed(float const speed_)
{
	// TODO: add support for other units than samp-default.
	if (this->isSpawned())
		this->setVelocity(this->getForwardVector() * speed_);
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::setVelocity(math::Vector3f const & velocity_)
{
	if (this->isSpawned())
		sampgdk_SetVehicleVelocity(this->getHandle(), velocity_.x, velocity_.y, velocity_.z);
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::setModel(std::int32_t const modelIndex_)
{
	m_modelIndex = modelIndex_;
	if (this->isSpawned())
		this->respawn();
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::setFirstColor(std::int32_t const color_)
{
	m_firstColor = color_;
	if (this->isSpawned())
		sampgdk_ChangeVehicleColor(this->getHandle(), m_firstColor, m_secondColor);
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::setSecondColor(std::int32_t const color_)
{
	m_secondColor = color_;
	if (this->isSpawned())
		sampgdk_ChangeVehicleColor(this->getHandle(), m_firstColor, m_secondColor);
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::installNitro()
{
	if (this->isSpawned())
		sampgdk_AddVehicleComponent(this->getHandle(), 1010);
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::uninstallNitro()
{
	if (this->isSpawned())
		sampgdk_RemoveVehicleComponent(this->getHandle(), 1010);
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::flip()
{
	if (this->isSpawned())
		this->setFacingAngle(this->getFacingAngle());
}

/////////////////////////////////////////////////////////////////////////////////
math::Vector3f Vehicle::getLocation() const
{
	math::Vector3f location = m_location;
	if (this->isSpawned())
		sampgdk_GetVehiclePos(this->getHandle(), &(location.x), &(location.y), &(location.z));
	return location;
}

/////////////////////////////////////////////////////////////////////////////////
math::Vector3f Vehicle::getVelocity() const
{
	math::Vector3f velocity;
	if (this->isSpawned())
		sampgdk_GetVehicleVelocity(this->getHandle(), &velocity.x, &velocity.y, &velocity.z);
	return velocity;
}

/////////////////////////////////////////////////////////////////////////////////
float Vehicle::getSpeed(const SpeedUnit unit_) const
{
	switch (unit_)
	{
	case SpeedUnit::KMPH:
		return this->getVelocity().length() * 179.78175f;
	case SpeedUnit::MPH:
		return this->getVelocity().length() * 112.36359f;
	default:
		return this->getVelocity().length();
	}
}

/////////////////////////////////////////////////////////////////////////////////
math::Vector3f Vehicle::getRotationAxis() const
{
	if(this->isSpawned())
	{
		float w, x, y, z;
		sampgdk_GetVehicleRotationQuat(this->getHandle(), &w, &x, &y, &z);
		return {
			std::asin(2 * y*z - 2 * x*w),
			-std::atan2(x*z + y * w, 0.5f - x * x - y * y),
			-std::atan2(x*y + z * w, 0.5f - x * x - z * z)
		};
	}
	return math::Vector3f();
}

/////////////////////////////////////////////////////////////////////////////////
math::Vector3f Vehicle::getForwardVector() const
{
	return {
		std::sin((-(this->getFacingAngle())) / 180.f * math::constants::Pi<float>),
		std::cos((-(this->getFacingAngle())) / 180.f * math::constants::Pi<float>),
		0 };
}

/////////////////////////////////////////////////////////////////////////////////
math::Vector3f Vehicle::getBackwardVector() const
{
	return -getForwardVector();
}

/////////////////////////////////////////////////////////////////////////////////
math::Vector3f Vehicle::getRightVector() const
{
	return {
		std::sin((-(this->getFacingAngle()) + 90) / 180.f * math::constants::Pi<float>),
		std::cos((-(this->getFacingAngle()) + 90) / 180.f * math::constants::Pi<float>),
		0 };
}

/////////////////////////////////////////////////////////////////////////////////
math::Vector3f Vehicle::getLeftVector() const
{
	return -getRightVector();
}

/////////////////////////////////////////////////////////////////////////////////
float Vehicle::getFacingAngle() const
{
	float angle = m_facingAngle;
	if (this->isSpawned())
		sampgdk_GetVehicleZAngle(this->getHandle(), &angle);
	return angle;
}

/////////////////////////////////////////////////////////////////////////////////
float Vehicle::getHealth() const
{
	float health = 1000;
	if (this->isSpawned())
		sampgdk_GetVehicleHealth(this->getHandle(), &health);
	return health;
}

/////////////////////////////////////////////////////////////////////////////////
Int32 Vehicle::getHandle() const
{
	return m_handle;
}

/////////////////////////////////////////////////////////////////////////////////
Int32 Vehicle::getModel() const
{
	return m_modelIndex;
}


/////////////////////////////////////////////////////////////////////////////////
Int32 Vehicle::getClientWorld() const
{
	if (this->isSpawned())
		return sampgdk_GetVehicleVirtualWorld( this->getHandle() );
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////
VehiclePlacement Vehicle::getPlacement() const
{
	return { this->getLocation(), this->getWorld(), this->getInterior() };
}

/////////////////////////////////////////////////////////////////////////////////
std::int32_t Vehicle::getFirstColor() const
{
	return m_firstColor;
}

/////////////////////////////////////////////////////////////////////////////////
std::int32_t Vehicle::getSecondColor() const
{
	return m_secondColor;
}

/////////////////////////////////////////////////////////////////////////////////
Clock::TimePoint Vehicle::getLatestUsage() const
{
	return this->isOccupied() ? Clock::now() : m_latestUsage;
}

/////////////////////////////////////////////////////////////////////////////////
Player* Vehicle::getDriver() const
{
	return m_passengers[0]; // seat 0 is a driver
}

/////////////////////////////////////////////////////////////////////////////////
bool Vehicle::isSpawned() const
{
	return m_handle != InvalidHandle;
}

/////////////////////////////////////////////////////////////////////////////////
bool Vehicle::isOccupied() const
{
	for (auto passenger : m_passengers)
	{
		if (passenger)
			return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////
bool Vehicle::spawn()
{
	if (!this->isSpawned() && m_modelIndex != -1)
	{
		m_handle = sampgdk_CreateVehicle(m_modelIndex, m_location.x, m_location.y, m_location.z, m_facingAngle, m_firstColor, m_secondColor, -1, false);
		// Respawn delay set to -1
		// This is because streamer will take advantage of vehicle respawning.
		// TODO: verify if this works ^^^.
		if (m_handle != InvalidHandle)
		{
			this->setInterior(m_interior);
			this->setWorld(m_world);
			return true;
		}
		// TODO: else condition:
		// log runtime error: failed to spawn vehicle (possibly upper limit reached).
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::despawn()
{
	if (this->isSpawned())
	{
		// Store some information about vehicle status.
		m_location = this->getLocation();
		m_facingAngle = this->getFacingAngle();

		for (auto &passenger : m_passengers)
		{
			if (passenger) {
				sampgdk_RemovePlayerFromVehicle(passenger->getIndex());
				passenger = nullptr;
			}
		}

		sampgdk_DestroyVehicle(m_handle);
	}
	m_handle = InvalidHandle;
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::setPlacementTracker(I3DNodePlacementTracker* tracker_)
{
	m_placementTracker = tracker_;
	this->sendPlacementUpdate();
}

/////////////////////////////////////////////////////////////////////////////////
I3DNodePlacementTracker* Vehicle::getPlacementTracker() const
{
	return m_placementTracker;
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::sendPlacementUpdate()
{
	if (m_placementTracker)
		m_placementTracker->whenPlacementUpdateReceived(this->getPlacement());
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::whenPlayerEnters(Player & player_, std::int32_t const seatIndex_)
{
	// TODO: remove below.
	//GameMode->sendDebug(String::format(Color::Red, "Player ", Color::White, player->getName(), Color::Red, " entered vehicle ", this->getHandle(), passenger ? " as a passenger." : " as a driver."));

	m_latestUsage = Clock::now();
	m_passengers[seatIndex_] = &player_;
}

/////////////////////////////////////////////////////////////////////////////////
void Vehicle::whenPlayerExits(Player & player_)
{
	//GameMode->sendDebug(String::format(Color::Red, "Player ", Color::White, player->getName(), Color::Red, " exited vehicle."));
	m_latestUsage = Clock::now();

	for (std::size_t i = 0; i < m_passengers.size(); i++)
	{
		if (m_passengers[i] == &player_) {
			m_passengers[i] = nullptr;
			break;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////
bool Vehicle::isValidForLazySpawn(std::int32_t const modelIndex_)
{
	return Vehicle::getModelCategory(modelIndex_) != VehicleCategory::Trailers && modelIndex_ != 538 && modelIndex_ != 537;
}

/////////////////////////////////////////////////////////////////////////////////
VehicleCategory Vehicle::getModelCategory(std::int32_t const modelIndex_)
{
	auto const it = std::find_if(g_vehiclesDataM.begin(), g_vehiclesDataM.end(),
		[modelIndex_](std::pair<int, TVehicleInfoT> const & vehInfo)
		{
			return vehInfo.first == modelIndex_;
		});

	if (it != g_vehiclesDataM.end()) {
		return std::get<4>(it->second);
	}
	return VehicleCategory::OffRoad;
}

/////////////////////////////////////////////////////////////////////////////////
std::int32_t Vehicle::findModelBestMatch(std::string const & name_, std::size_t const minimalScore_)
{
	std::int32_t modelIndex	= -1;
	std::size_t	maxScore	= 0;
	for (auto const &it : g_vehiclesDataM)
	{
		const TVehicleInfoT &info = it.second;
		auto [itMin, itMax] = text::ascii::searchWithIncomplete<text::CaseInsensitive>(text::ascii::toLower(name_), text::ascii::toLower(std::string{ std::get<1>(info) }));
		auto score = itMax - itMin;
		if (score > maxScore)
		{
			modelIndex	= it.first;
			maxScore	= score;
		}
	}
	return (maxScore >= minimalScore_ ? modelIndex : -1);
}

/////////////////////////////////////////////////////////////////////////////////
math::Vector3f Vehicle::getModelSize(std::int32_t const modelIndex_)
{
	math::Vector3f size;
	sampgdk_GetVehicleModelInfo(modelIndex_, VEHICLE_MODEL_INFO_SIZE, &size.x, &size.y, &size.z);
	return size;
}

/////////////////////////////////////////////////////////////////////////////////
StaticVehicle::StaticVehicle()
	:
	m_spawnAngle{ 0 },
	m_spawnWorld{ 0 },
	m_spawnInterior{ 0 },
	m_spawnFirstColor{ 0 },
	m_spawnSecondColor{ 0 }
{
}

/////////////////////////////////////////////////////////////////////////////////
void StaticVehicle::setSpawnLocation(math::Vector3f const & location_)
{
	m_spawnLocation = location_;
}

/////////////////////////////////////////////////////////////////////////////////
void StaticVehicle::setSpawnFacingAngle(float const angle_)
{
	m_spawnAngle = angle_;
}

/////////////////////////////////////////////////////////////////////////////////
void StaticVehicle::setSpawnWorld(std::int32_t const world_)
{
	m_spawnWorld = world_;
}

/////////////////////////////////////////////////////////////////////////////////
void StaticVehicle::setSpawnInterior(std::int32_t const interior_)
{
	m_spawnInterior = interior_;
}

/////////////////////////////////////////////////////////////////////////////////
void StaticVehicle::setSpawnFirstColor(std::int32_t const firstColor_)
{
	m_spawnFirstColor = firstColor_;
}

/////////////////////////////////////////////////////////////////////////////////
void StaticVehicle::setSpawnSecondColor(std::int32_t const secondColor_)
{
	m_spawnSecondColor = secondColor_;
}

/////////////////////////////////////////////////////////////////////////////////
void StaticVehicle::restoreToSpawn()
{
	m_latestUsage = Clock::now();
	this->setLocation(m_spawnLocation);
	this->setFacingAngle(m_spawnAngle);
	this->setWorld(m_spawnWorld);
	this->setInterior(m_spawnInterior);
	this->setFirstColor(m_spawnFirstColor);
	this->setSecondColor(m_spawnSecondColor);

	this->repair();
}

/////////////////////////////////////////////////////////////////////////////////
math::Vector3f StaticVehicle::getSpawnLocation() const
{
	return m_spawnLocation;
}

/////////////////////////////////////////////////////////////////////////////////
float StaticVehicle::getSpawnFacingAngle() const
{
	return m_spawnAngle;
}

/////////////////////////////////////////////////////////////////////////////////
std::int32_t StaticVehicle::getSpawnWorld() const
{
	return m_spawnWorld;
}

/////////////////////////////////////////////////////////////////////////////////
std::int32_t StaticVehicle::getSpawnInterior() const
{
	return m_spawnInterior;
}

/////////////////////////////////////////////////////////////////////////////////
std::int32_t StaticVehicle::getSpawnFirstColor() const
{
	return m_spawnFirstColor;
}

/////////////////////////////////////////////////////////////////////////////////
std::int32_t StaticVehicle::getSpawnSecondColor() const
{
	return m_spawnSecondColor;
}

} // namespace agdk