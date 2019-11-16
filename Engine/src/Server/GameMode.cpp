#include SAMPEDGENGINE_PCH

// Custom includes:
#include <SAMP-EDGEngine/Server/GameMode.hpp>
#include <SAMP-EDGEngine/World/Streamer/Streamer.hpp>

#include <SAMP-EDGEngine/Server/Server.hpp>

namespace samp_cpp
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IGameMode::IGameMode(ServerClass & server_)
	:
	server{ server_ }
#ifdef DEBUG
	, m_debugLogOutput{ *this }
#endif
{
	#ifdef DEBUG
		debugLog.setOutput(&m_debugLogOutput);
	#endif

	server.onServerUpdate += { *this, &IGameMode::onServerUpdate };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IGameMode::~IGameMode()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UniquePtr<Player> IGameMode::newPlayerInstance(Int32 playerIndex_)
{
	return std::make_unique<Player>(*this, playerIndex_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IGameMode::addPlayerClass(std::size_t modelIndex_, math::Vector3f const location_, float const facingAngle_, std::array<Weapon, 3> weapons_)
{
	sampgdk_AddPlayerClass(modelIndex_, location_.x, location_.y, location_.z, facingAngle_,
		static_cast<Int32>(weapons_[0].getType()), weapons_[0].getAmmo(),
		static_cast<Int32>(weapons_[1].getType()), weapons_[1].getAmmo(),
		static_cast<Int32>(weapons_[2].getType()), weapons_[2].getAmmo());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IGameMode::sendDeathMessage(Player const* left_, Player const * right_, Weapon::Type weapon_)
{
	sampgdk_SendDeathMessage(
			left_ ? left_->getIndex() : -1,
			right_ ? right_->getIndex() : -1,
			static_cast<Int32>(weapon_)
		);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IGameMode::setup()
{
	this->setupStreamer();
	this->setupEvents();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IGameMode::setupStreamer()
{
	streamer = std::make_unique<default_streamer::Streamer>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IGameMode::onServerUpdate(double deltaTime_, IUpdatable::TimePoint timePoint_)
{
	tasks.update(deltaTime_, timePoint_);
}

}
