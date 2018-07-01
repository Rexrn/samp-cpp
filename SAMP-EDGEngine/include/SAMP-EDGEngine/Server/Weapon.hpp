// File description:
// Implements C++-way Weapon management and traits.
#pragma once

#include SAMP_EDGENGINE_PCH

#include <SAMP-EDGEngine/Core/TypesAndDefinitions.hpp>

namespace agdk
{	
/// <summary>
/// This class is used to define weapon type and ammunition.
/// </summary>
class Weapon
{
public:
	enum Type
	{
		Invalid				= -1,
		Fist				= 0,
		BrassKnuckles		= WEAPON_BRASSKNUCKLE,
		GolfClub			= WEAPON_GOLFCLUB,
		NightStick			= WEAPON_NITESTICK,
		Knife				= WEAPON_KNIFE,
		BaseballBat			= WEAPON_BAT,
		Shovel				= WEAPON_SHOVEL,
		PoolCue				= WEAPON_POOLSTICK,
		Katana				= WEAPON_KATANA,
		Chainsaw			= WEAPON_CHAINSAW,
		PurpleDildo			= WEAPON_DILDO,
		Dildo				= WEAPON_DILDO2,
		Vibrator			= WEAPON_VIBRATOR,
		SilverVibrator		= WEAPON_VIBRATOR2,
		Flowers				= WEAPON_FLOWER,
		Cane				= WEAPON_CANE,
		Grenade				= WEAPON_GRENADE,
		TearGas				= WEAPON_TEARGAS,
		Molotov				= WEAPON_MOLTOV,
		Colt45				= WEAPON_COLT45,
		Silencer			= WEAPON_SILENCED,
		Deagle				= WEAPON_DEAGLE,
		Shotgun				= WEAPON_SHOTGUN,
		SawnOff				= WEAPON_SAWEDOFF,
		CombatShotgun		= WEAPON_SHOTGSPA,
		UZI					= WEAPON_UZI,
		MP5					= WEAPON_MP5,
		AK47				= WEAPON_AK47,
		M4					= WEAPON_M4,
		Tec9				= WEAPON_TEC9,
		CountryRifle		= WEAPON_RIFLE,
		SniperRifle			= WEAPON_SNIPER,
		RPG					= WEAPON_ROCKETLAUNCHER,
		HSRocket			= WEAPON_HEATSEEKER,
		Flamethrower		= WEAPON_FLAMETHROWER,
		Minigun				= WEAPON_MINIGUN,
		SatchelCharge		= WEAPON_SATCHEL,
		Detonator			= WEAPON_BOMB,
		Spraycan			= WEAPON_SPRAYCAN,
		FireExtinguisher	= WEAPON_FIREEXTINGUISHER,
		Camera				= WEAPON_CAMERA,
		NightVision			= WEAPON_NIGHTVISION,
		ThermalGoggles		= 45,
		Parachute			= 46,
		FakePistolDMG		= 47,
		VehicleDMG			= 49,
		HelicopterDMG		= 50,
		ExplosionDMG		= 51,
		DrownDMG			= 53,
		FallDMG				= 54,
		Connect				= 200,
		Disconnect			= 201,
		Suicide				= 255
	};

	// Helper typedefs.
	using GetNameFnRef		= std::string(&)(Weapon::Type const);
	using GetNameFnPtr		= std::string(*)(Weapon::Type const);
	

	struct HitResult
	{
		enum Target
		{
			None,
			NPC,
			Player,
			Vehicle,
			Object,
			PlayerObject
		};
		
		/// <summary>
		/// Initializes a new instance of the <see cref="HitResult"/> struct.
		/// </summary>
		HitResult()
			:
			target{ None },
			targetHandle{ -1 }
		{
		}
		
		/// <summary>
		/// Initializes a new instance of the <see cref="HitResult"/> struct.
		/// </summary>
		/// <param name="target_">The target.</param>
		/// <param name="targetHandle_">The target handle.</param>
		/// <param name="location_">The location.</param>
		HitResult(Target target_, Int32 targetHandle_, math::Vector3f location_)
			:
			target{ target_ }, 
			targetHandle{ targetHandle_ },
			location{ location_ }
		{
			
		}

		Target			target;
		Int32			targetHandle;
		math::Vector3f	location;
	};

	/// <summary>
	/// Class containing default parameters/methods.
	/// </summary>
	class Default
	{
	public:			
		/// <summary>
		/// Don't allow to create instance of this class.
		/// </summary>
		Default() = delete;
			
		/// <summary>
		/// Default function to obtain weapon name by passing its type as parameter.
		/// </summary>
		/// <param name="type">The weapon type.</param>
		/// <returns>Weapon name.</returns>
		static std::string getName(Weapon::Type const type_);
	};
		
	/// <summary>
	/// Initializes a new instance of the <see cref="Weapon"/> class.
	/// </summary>
	constexpr Weapon()
		: m_type{ Type::Fist }, m_ammo{ 1 }
	{
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="Weapon"/> class.
	/// </summary>
	/// <param name="type">The type.</param>
	/// <param name="ammo">The ammo.</param>
	constexpr Weapon(Weapon::Type const type_, std::int32_t const ammo_ = 1)
		: m_type{ type_ }, m_ammo{ ammo_ }
	{
	}
		
	/// <summary>
	/// Searches for weapon of name `name_`.
	/// This function is NOT case sensitive because it is useless in this case.
	///	You can use your own get[Weapon]Name function by changing `Weapon::getNameFn`.
	/// </summary>
	/// <param name="name_">The weapon name.</param>
	/// <returns>Weapon type</returns>
	static Weapon::Type findByName(std::string_view const name_);

	/// <summary>
	/// Searches for weapon of name/index `name_`.
	/// This function is NOT case sensitive because it is useless in this case.
	///	You can use your own get[Weapon]Name function by changing `Weapon::getNameFn`.
	/// </summary>
	/// <param name="name_">The weapon name or index.</param>
	/// <returns>Weapon type</returns>
	static Weapon::Type findByNameOrType(std::string_view const name_);

	/// <summary>
	/// Searches for weapon of name/index `name_`.
	/// It accepts incomplete name (for example: "sniper", "sawn").
	///	You can use your own get[Weapon]Name function by changing `Weapon::getNameFn`.
	/// </summary>
	/// <param name="name_">The weapon name/index.</param>
	/// <returns>Weapon type</returns>
	static Weapon::Type findBestMatch(std::string_view const name_);

	/// <summary>
	/// Determines whether `type_` is weapon type.
	/// Inside Weapon::Type enum both weapon and damage types are stored.
	/// </summary>
	/// <param name="type_">The type.</param>
	/// <returns>
	///   <c>true</c> if `type_` is weapon type; otherwise, <c>false</c>.
	/// </returns>
	constexpr static bool isWeaponType(Weapon::Type const type_) {
		return type_ >= Fist && type_ <= Parachute;
	}

	/// <summary>
	/// Determines whether `type_` is damage type.
	/// Inside Weapon::Type enum both weapon and damage types are stored.
	/// </summary>
	/// <param name="type_">The type.</param>
	/// <returns>
	///   <c>true</c> if `type_` is damage type; otherwise, <c>false</c>.
	/// </returns>
	constexpr static bool isDamageType(Weapon::Type const type_) {
		return	type_ == FakePistolDMG	|| type_ == VehicleDMG	|| type_ == HelicopterDMG ||
				type_ == ExplosionDMG	|| type_ == DrownDMG	|| type_ == FallDMG	||
				type_ == Suicide;
	}

	/// <summary>
	/// Determines whether instance is weapon.
	/// Inside Weapon::Type enum both weapon and damage types are stored.
	/// </summary>
	/// <param name="type_">The type.</param>
	/// <returns>
	///   <c>true</c> if instance is weapon; otherwise, <c>false</c>.
	/// </returns>
	constexpr bool isWeapon() const {
		return Weapon::isWeaponType(m_type);
	}

	/// <summary>
	/// Determines whether instance is damage.
	/// Inside Weapon::Type enum both weapon and damage types are stored.
	/// </summary>
	/// <param name="type_">The type.</param>
	/// <returns>
	///   <c>true</c> if instance is damage; otherwise, <c>false</c>.
	/// </returns>
	constexpr bool isDamage() const {
		return Weapon::isDamageType(m_type);
	}

	/// <summary>
	/// Sets weapon ammunition, does not affect player!
	///	If you want to set player's weapon ammo use `Player::setWeaponAmmo`
	/// </summary>
	/// <param name="ammo_">The count of ammunition.</param>
	constexpr void setAmmo(std::int32_t const ammo_) {
		m_ammo = ammo_;
	}

	/// <summary>
	/// Gets the weapon name.
	///	You can use your own get[Weapon]Name function by changing `Weapon::getNameFn`.
	/// </summary>
	/// <returns>Weapon name</returns>
	std::string	getName() const;
		
	/// <summary>
	/// Returns the weapon type.
	/// </summary>
	/// <returns></returns>
	constexpr Weapon::Type getType() const {
		return m_type;
	}
	
	/// <summary>
	/// Returns weapon ammunition count.
	/// </summary>
	/// <returns></returns>
	constexpr std::int32_t getAmmo() const {
		return m_ammo;
	}

	/// <summary>
	/// Returns type of a weapon converted to 32-bit integer.
	/// </summary>
	/// <returns></returns>
	constexpr std::int32_t getTypeIndex() const {
		return static_cast<std::int32_t>(m_type);
	}
private:

	//	Stores weapon type
	Weapon::Type	m_type;
	//	Stores weapon ammo
	std::int32_t	m_ammo;


	/// <summary>
	/// Pointer to function for obtaining weapon name.
	/// If your gamemode uses different weapon names, switch this function to your own.
	/// </summary>
	static GetNameFnPtr getNameFn; // = Weapon::Default::getName
};

/// <summary>
/// Class used to store multiple weapons.
/// </summary>
class WeaponSet
{
public:		
	/// <summary>
	/// Initializes a new instance of the empty <see cref="WeaponSet"/> class.
	/// </summary>
	WeaponSet() = default;
		
	/// <summary>
	/// Initializes a new copy of the <see cref="WeaponSet"/> class.
	/// </summary>
	/// <param name="other_">The other weapon set.</param>
	WeaponSet(const WeaponSet &other_) = default;
		
	/// <summary>
	/// Initializes a new instance of the <see cref="WeaponSet"/> class.
	/// </summary>
	/// <param name="weapons_">Vector of weapons.</param>
	explicit WeaponSet(std::vector<Weapon> const & weapons_);

	/// <summary>
	/// Adds the specified weapon to weapon set.
	/// </summary>
	/// <param name="weapon">The weapon.</param>
	void add(Weapon const weapon_);

	/// <summary>
	/// Removes ammunition from specified weapon type.
	/// The default value of `ammo_` (-1) means it will remove all ammo.
	/// </summary>
	/// <param name="type_">The weapon type.</param>
	/// <param name="ammo_">The count of ammunition.</param>
	void remove(Weapon::Type const type_, std::int32_t const ammo_ = -1);

	/// <summary>
	/// Sets weapon ammo.
	/// If specified weapon type is not inside weapon set it will add this weapon.
	/// </summary>
	/// <param name="type_">The weapon type.</param>
	/// <param name="ammo_">The count of ammunition.</param>
	void setAmmo(Weapon::Type const type_, std::int32_t const ammo_);
	
	/// <summary>
	/// Returns ref to the weapons vector.
	/// </summary>
	/// <returns>Ref to weapons vector.</returns>
	std::vector<Weapon> &getWeapons() {
		return m_weapons;
	};
	
	/// <summary>
	/// Returns copy of the weapons vector.
	/// </summary>
	/// <returns>Copy of the weapons vector.</returns>
	std::vector<Weapon> getWeapons() const {
		return m_weapons;
	}
private:
	/// Weapons list (vector).
	std::vector <Weapon> m_weapons;
};
}
