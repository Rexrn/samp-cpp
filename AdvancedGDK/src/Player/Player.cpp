#include <Player/Player.hpp>

namespace agdk
{
	///////////////////////////////////////////////////////////////////////////
	Player::Player(const std::size_t index_)
		:	m_index{ index_ }, m_spawned{ false },
			m_score{ 0 }, m_cash{ 0 },
			m_health{ 100 }, m_armour{ 0 }
	{
	}

	///////////////////////////////////////////////////////////////////////////
	bool Player::setName(const std::string_view name_)
	{
		// TODO: implement this.
		return false;
	}

	///////////////////////////////////////////////////////////////////////////
	void Player::setLocation(const Vector3 location_)
	{
		m_lastLocation = location_;
		if (this->isSpawned())
			sampgdk::SetPlayerPos(this->getIndex(), location_.x, location_.y, location_.z);
	}

	///////////////////////////////////////////////////////////////////////////
	void Player::setFacingAngle(const float angle_)
	{
		if (this->isSpawned())
			sampgdk::SetPlayerFacingAngle(this->getIndex(), angle_);
	}

	///////////////////////////////////////////////////////////////////////////
	void Player::setHealth(const float health_)
	{
		m_health = health_ + cxprHealthBase;
		if (this->isSpawned())
			sampgdk::SetPlayerHealth(this->getIndex(), m_health);
	}

	///////////////////////////////////////////////////////////////////////////
	void Player::setArmour(const float armour_)
	{
		m_armour = armour_;
		if (this->isSpawned())
			sampgdk::SetPlayerArmour(this->getIndex(), m_armour);
	}
}