#include "AdvancedGDKPCH.hpp" // PCH

// Custom includes:
#include <AdvancedGDK/Server/Player/Player.hpp>
#include <AdvancedGDK/Server/Server.hpp>
#include <AdvancedGDK/Core/Text/ASCII.hpp>

namespace agdk
{
	///////////////////////////////////////////////////////////////////////////
	Player::Player(std::size_t const index_)
		:	m_index{ index_ }, m_spawned{ false },
			m_score{ 0 }, m_cash{ 0 },
			m_health{ 100 }, m_armour{ 0 }
	{
		m_name = this->getClientName();
	}

	///////////////////////////////////////////////////////////////////////////
	bool Player::setName(std::string_view const name_, bool(*isNameValidProc_)(const std::string_view))
	{
		// If passed null pointer use the default method.
		if (isNameValidProc_ == nullptr)
			isNameValidProc_ = &Server::Default::isPlayerNameValid;

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
		if (this->isSpawned())
			sampgdk_SetPlayerPos(this->getIndex(), location_.x, location_.y, location_.z);
	}

	///////////////////////////////////////////////////////////////////////////
	void Player::setFacingAngle(float const angle_)
	{
		if (this->isSpawned())
			sampgdk_SetPlayerFacingAngle(this->getIndex(), angle_);
	}

	///////////////////////////////////////////////////////////////////////////
	void Player::setWorld(std::int32_t const world_)
	{
		if (this->isSpawned())
			sampgdk_SetPlayerVirtualWorld(this->getIndex(), world_);
	}

	///////////////////////////////////////////////////////////////////////////
	void Player::setInterior(std::int32_t const interior_)
	{
		if (this->isSpawned())
			sampgdk_SetPlayerInterior(this->getIndex(), interior_);
	}

	///////////////////////////////////////////////////////////////////////////
	void Player::setHealth(float const health_)
	{
		m_health = health_ + cxHealthBase;
		if (this->isSpawned())
			sampgdk_SetPlayerHealth(this->getIndex(), m_health);
	}

	///////////////////////////////////////////////////////////////////////////
	void Player::setArmour(float const armour_)
	{
		m_armour = armour_;
		if (this->isSpawned())
			sampgdk_SetPlayerArmour(this->getIndex(), m_armour);
	}

	///////////////////////////////////////////////////////////////////////////
	void Player::addWeapon(Weapon const weapon_)
	{
		sampgdk_GivePlayerWeapon(this->getIndex(), weapon_.getTypeIndex(), weapon_.getAmmo());
	}
}