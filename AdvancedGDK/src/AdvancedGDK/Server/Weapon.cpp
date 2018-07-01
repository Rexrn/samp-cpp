#include "AdvancedGDKPCH.hpp" // PCH

#include <AdvancedGDK/Server/Weapon.hpp>

#include <AdvancedGDK/Core/Text/ASCII.hpp>

namespace agdk
{
	// Initialize default Weapon variables
	Weapon::GetNameFnPtr Weapon::getNameFn = &Weapon::Default::getName;

	///////////////////////////////////////////////////////////////////////////////////
	Weapon::Type Weapon::findByName(std::string_view const name_)
	{
		// "getNameFn" is a null pointer!
		// It is a programmer's fault, fix it.
		assert(Weapon::getNameFn != nullptr);

		// We can't avoid creating copy of the string.
		std::string cpName{ name_ };
		cpName = text::ascii::toLower(cpName);
		for (std::int32_t i = Fist; i <= Parachute; i++)
		{
			if ( cpName == text::ascii::toLower( Weapon::getNameFn(static_cast<Weapon::Type>(i)) ) )
				return static_cast<Weapon::Type>(i);
		}
		return Weapon::Invalid;
	}

	///////////////////////////////////////////////////////////////////////////////////
	Weapon::Type Weapon::findByNameOrType(std::string_view const name_)
	{
		Weapon::Type result = Weapon::Invalid;

		{
			// We can't avoid creating copy of the string.
			std::string cpName{ name_ };

			std::int32_t weaponType = 0;

			if (std::istringstream istream{ cpName };
			istream >> weaponType)
			{
				result = static_cast<Weapon::Type>(weaponType);

				if (!Weapon::isWeaponType(result))
					result = Weapon::Invalid;
			}
		}

		if (result == Weapon::Invalid) {
			result = Weapon::findByName(name_);
		}
		return result;
	}

	///////////////////////////////////////////////////////////////////////////////////
	Weapon::Type Weapon::findBestMatch(std::string_view const name_)
	{
		// "getNameFn" is a null pointer!
		// It is a programmer's fault, fix it.
		assert(Weapon::getNameFn != nullptr);

		Weapon::Type result = Weapon::Invalid;

		// We can't avoid creating copy of the string.
		std::string cpName{ name_ };

		{
			std::int32_t weaponType = 0;

			if (std::istringstream istream{ cpName };
			istream >> weaponType)
			{
				result = static_cast<Weapon::Type>(weaponType);

				if (!Weapon::isWeaponType(result))
					result = Weapon::Invalid;
			}
		}

		if (result == Weapon::Invalid)
		{
			result = findByName(name_);

			if (result == Weapon::Invalid)
			{
				std::size_t	score		= 0;
				Weapon::Type mostScored	= Weapon::Invalid;
				std::string compareName = text::ascii::toLower(cpName);

				for (std::int32_t i = Fist; i <= Parachute; i++)
				{
					// Search for max sequence in the string.
					auto const [itMin, itMax] = text::ascii::searchWithIncomplete<text::CaseInsensitive>(compareName,
						text::ascii::toLower(
							Weapon::getNameFn( static_cast<Weapon::Type>(i) )
						));

					auto const tempScore = itMax - itMin;
					if (tempScore > score) {
						score		= tempScore;
						mostScored	= static_cast<Weapon::Type>(i);
					}
				}

				// Score must be at least 1, otherwise none is returned.
				if (score > 0)
					result = mostScored;
			}
		}
		return result;
	}

	///////////////////////////////////////////////////////////////////////////////////
	std::string Weapon::getName() const
	{
		// "getNameFn" is a null pointer!
		// It is a programmer's fault, fix it.
		assert(Weapon::getNameFn != nullptr);

		return Weapon::getNameFn(this->getType());
	}

	///////////////////////////////////////////////////////////////////////////////////
	std::string Weapon::Default::getName(const Weapon::Type type)
	{
		switch (type)
		{
		case Weapon::Fist:				return "Fist";
		case Weapon::BrassKnuckles:		return "BrassKnuckle";
		case Weapon::GolfClub:			return "GolfClub";
		case Weapon::NightStick:		return "Nightstick";
		case Weapon::Knife:				return "Knife";
		case Weapon::BaseballBat:		return "BaseballBat";
		case Weapon::Shovel:			return "Shovel";
		case Weapon::PoolCue:			return "PoolCue";
		case Weapon::Katana:			return "Katana";
		case Weapon::Chainsaw:			return "Chainsaw";
		case Weapon::PurpleDildo:		return "PurpleDildo";
		case Weapon::Dildo:				return "Dildo";
		case Weapon::Vibrator:			return "Vibe";
		case Weapon::SilverVibrator:	return "SilverVibe";
		case Weapon::Flowers:			return "Flowers";
		case Weapon::Cane:				return "Cane";
		case Weapon::Grenade:			return "Grenade";
		case Weapon::TearGas:			return "TearGas";
		case Weapon::Molotov:			return "Molotov";
		case Weapon::Colt45:			return "Pistol";
		case Weapon::Silencer:			return "Silencer";
		case Weapon::Deagle:			return "Deagle";
		case Weapon::Shotgun:			return "Shotgun";
		case Weapon::SawnOff:			return "SawnOff";
		case Weapon::CombatShotgun:		return "Combat";
		case Weapon::UZI:				return "UZI";
		case Weapon::MP5:				return "MP5";
		case Weapon::AK47:				return "AK47";
		case Weapon::M4:				return "M4";
		case Weapon::Tec9:				return "Tec9";
		case Weapon::CountryRifle:		return "Rifle";
		case Weapon::SniperRifle:		return "SniperRifle";
		case Weapon::RPG:				return "RPG";
		case Weapon::HSRocket:			return "HSRocket";
		case Weapon::Flamethrower:		return "Flamethrower";
		case Weapon::Minigun:			return "Minigun";
		case Weapon::SatchelCharge:		return "SatchelCharge";
		case Weapon::Detonator:			return "Detonator";
		case Weapon::Spraycan:			return "Spraycan";
		case Weapon::FireExtinguisher:	return "FireExtinguisher";
		case Weapon::Camera:			return "Camera";
		case Weapon::NightVision:		return "NightVision";
		case Weapon::ThermalGoggles:	return "ThermalGoogles";
		case Weapon::Parachute:			return "Parachute";
		case Weapon::FakePistolDMG:		return "FakePistol";
		case Weapon::VehicleDMG:		return "Car";
		case Weapon::HelicopterDMG:		return "Heli";
		case Weapon::ExplosionDMG:		return "Explosion";
		case Weapon::DrownDMG:			return "Drowning";
		case Weapon::FallDMG:			return "Fall";
		case Weapon::Connect:			return "Connection";
		case Weapon::Disconnect:		return "Disconnection";
		case Weapon::Suicide:			return "Suicide";
		default: return " ";
		}
	}

	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	WeaponSet::WeaponSet(std::vector<Weapon> const & weapons_)
		: m_weapons{ weapons_ }
	{
	}

	///////////////////////////////////////////////////////////////////////////////////
	void WeaponSet::add(Weapon const weapon_)
	{
		auto it = std::find_if(m_weapons.begin(), m_weapons.end(),
			[weapon_](const Weapon &w_) {
			return w_.getType() == weapon_.getType();
		});

		if (it != m_weapons.end()) {
			it->setAmmo(it->getAmmo() + weapon_.getAmmo());
		}
		else
			m_weapons.push_back(weapon_);
	}

	///////////////////////////////////////////////////////////////////////////////////
	void WeaponSet::remove(Weapon::Type const type_, std::int32_t const ammo_)
	{
		auto it = std::find_if(m_weapons.begin(), m_weapons.end(),
			[type_](const Weapon &w_) {
			return w_.getType() == type_;
		});

		if (it != m_weapons.end())
		{
			Weapon &weapon = *it;
			if (weapon.getAmmo() <= ammo_) {
				m_weapons.erase(it);
			}
			else {
				weapon.setAmmo(weapon.getAmmo() - ammo_);
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////////
	void WeaponSet::setAmmo(Weapon::Type const type_, const std::int32_t ammo_)
	{
		// Ammo must be at least 0 in this case, fix it.
		assert(ammo_ >= 0);
		
		if (ammo_ == 0)
			this->remove(type_);
		else
		{
			auto it = std::find_if(m_weapons.begin(), m_weapons.end(),
				[type_](const Weapon &w_) {
				return w_.getType() == type_;
			});

			if (it != m_weapons.end()) {
				it->setAmmo(ammo_);
			}
			else {
				this->add( Weapon{ type_, ammo_ } );
			}
		}
	}
}
