#include "stdafx.h" // PCH

// Custom includes:
#include <AdvancedGDK/Player/Player.hpp>
#include <AdvancedGDK/Server/Server.hpp>
#include <AdvancedGDK/Misc/String.hpp>

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
	bool Player::setName(const std::string_view name_, bool(*isNameValidProc_)(const std::string_view))
	{
		// If passed null pointer use the default method.
		if (isNameValidProc_ == nullptr)
			isNameValidProc_ = &Server::Default::isPlayerNameValid;

		if (isNameValidProc_(name_))
		{
			// Store requested name (we are forced to copy the string, since SAMPGDK requires null terminated C-string).
			std::string newName{ name_ };
			if (StringHelper::equals(name_, this->getName()))
			{
				// Store temporarily modified name.
				std::string tempName{ name_ };

				// We need to change name to some `name_`+"_" string, because it is invalid in SAMP
				// to change name from f.e. "FooBar" to "foobar".
				if (tempName.length() < 21)
					tempName += std::string(21 - tempName.length(), '_');

				sampgdk::SetPlayerName(this->getIndex(), tempName.c_str());
				sampgdk::SetPlayerName(this->getIndex(), newName.c_str());
			}
			else
				sampgdk::SetPlayerName(this->getIndex(), newName.c_str());
			return true;
		}
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