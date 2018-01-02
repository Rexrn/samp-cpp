/**
 * Header: Player.hpp
 * Author: Pawe³ Syska aka RazzorFlame.
 * Description:
 * Implements basic Player class.
**/

#pragma once

// SAMPGDK include:
#include <AdvancedGDK/SampGDK.hpp>

// Custom includes:
#include <AdvancedGDK/Misc/Math.hpp>

// Standard includes:
#include <memory>		// for std::shared_ptr
#include <cstddef>		// for std::size_t
#include <string_view>

namespace agdk
{	
	class PlayerAgent;

	/// <summary>
	/// Class wrapping SAMP player data into class.
	/// </summary>
	class Player
		: public std::enable_shared_from_this<Player>
	{
	public:		

		// Some constants
		static constexpr float cxprHealthBase = 256 * 100.f;


		/// <summary>
		/// Initializes a new instance of the <see cref="Player"/> class.
		/// </summary>
		/// <param name="index">Index of the player.</param>
		explicit Player(const std::size_t index_);
		
		/// <summary>
		/// Default constructor (deleted, use explicit index constructor instead).
		/// </summary>
		Player() = delete;

		/// <summary>
		/// Copy onstructor (deleted, use explicit index constructor instead).
		/// </summary>
		Player(const Player &)	= delete;

		/// <summary>
		/// Move constructor (deleted, use explicit index constructor instead).
		/// </summary>
		Player(Player &&)		= delete;		

		// Player data.		

		/// <summary>
		/// Sets player name.
		/// </summary>
		/// <param name="name_">The name.</param>
		/// <returns>
		///   <c>true</c> if succeeded; otherwise, <c>false</c>.
		/// </returns>
		bool setName(const std::string_view name_, bool(*isNameValidProc_)(const std::string_view) = nullptr);

		// Player world transform.

		/// <summary>
		/// Sets the player's location.
		/// </summary>
		/// <param name="location_">The location.</param>
		void setLocation(const Vector3 location_);
		
		/// <summary>
		/// Sets player's facing angle.
		/// </summary>
		/// <param name="angle_">The angle.</param>
		void setFacingAngle(const float angle_);
		
		// Player condition.

		/// <summary>
		/// Sets player's health.
		/// </summary>
		/// <param name="health_">The health.</param>
		void setHealth(const float health_);

		/// <summary>
		/// Sets player's armour.
		/// </summary>
		/// <param name="armour_">The armour.</param>
		void setArmour(const float armour_);
		
		/// <summary>
		/// Damages the player.
		/// </summary>
		/// <param name="damage_">The damage count.</param>
		void damage(const float damage_);
		// TODO: uncomment this, implement damage. void addDamage(const float damage_, const EDamageType type_ = NonPhysical);

		// Player data.

		/// <summary>
		/// Returns player index.
		/// </summary>
		/// <returns>Player index (std::size_t).</returns>
		std::size_t getIndex() const noexcept {
			return m_index;
		}
		
		/// <summary>
		/// Returns player name.
		/// </summary>
		/// <returns>Player name.</returns>
		std::string getName() const {
			return m_name;
		}
		
		// Player world transform.

		/// <summary>
		/// Returns the player location.
		/// </summary>
		/// <returns>Player location.</returns>
		Vector3 getLocation() const {
			return (this->isSpawned() ? this->getClientLocation() : m_lastLocation);
		}
				
		/// <summary>
		/// Returns the distance to specified location.
		/// </summary>
		/// <param name="location_">The location.</param>
		/// <returns>Distance to specified location.</returns>
		Meters getDistanceTo(const Vector3 location_) const {
			return Meters{ static_cast<Meters::ValueType>(this->getLocation().distance(location_)) };
		}
		
		/// <summary>
		/// Returns player facing angle.
		/// </summary>
		/// <returns>Player facing angle.</returns>
		float getFacingAngle() const {
			if (this->isSpawned())
			{
				float angle{ 0.f };
				if (sampgdk::GetPlayerFacingAngle(this->getIndex(), &angle))
					return angle;
			}
			return 0.0;
		}

		// Player statistics.
		
		/// <summary>
		/// Returns player's score.
		/// </summary>
		/// <returns>Player's score.</returns>
		std::int32_t getScore() const {
			return m_score;
		}

		/// <summary>
		/// Returns player's cash.
		/// </summary>
		/// <returns>Player's cash.</returns>
		std::int32_t getCash() const {
			return m_cash;
		}
				
		// Player condition.

		/// <summary>
		/// Returns player's health.
		/// </summary>
		/// <returns>Player's health</returns>
		float getHealth() const {
			return m_health - cxprHealthBase;
		}

		/// <summary>
		/// Returns player's armour.
		/// </summary>
		/// <returns>Player's armour</returns>
		float getArmour() const {
			return m_armour;
		}

		// Player status.

		/// <summary>
		/// Determines whether this player is spawned.
		/// </summary>
		/// <returns>
		///   <c>true</c> if this player is spawned; otherwise, <c>false</c>.
		/// </returns>
		bool isSpawned() const noexcept {
			return m_spawned;
		}
				
		/// <summary>
		/// Determines whether this player is dead.
		/// </summary>
		/// <returns>
		///   <c>true</c> if player is dead; otherwise, <c>false</c>.
		/// </returns>
		bool isDead() const noexcept {
			return m_health <= cxprHealthBase;
		}

		/// <summary>
		/// Determines whether client is dead.
		/// </summary>
		/// <returns>
		///   <c>true</c> if client is dead; otherwise, <c>false</c>.
		/// </returns>
		bool isClientDead() const {
			return this->getClientHealth() <= 0;
		}
	protected:
				
		/// <summary>
		/// Returns the client health.
		/// </summary>
		/// <returns>Client health.</returns>
		float getClientHealth() const {
			float health{ 0.f };
			sampgdk::GetPlayerHealth(this->getIndex(), &health);
			return health;
		}

		/// <summary>
		/// Returns the client armour.
		/// </summary>
		/// <returns>Client armour.</returns>
		float getClientArmour() const {
			float armour{ 0.f };
			sampgdk::GetPlayerArmour(this->getIndex(), &armour);
			return armour;
		}

	private:
		
		/// <summary>
		/// Returns the client location.
		/// </summary>
		/// <returns>Client location.</returns>
		/// <remarks>
		/// <para>This function is not accurate when player is not spawned, therefore you are forced to use <see cref="Player::getLocation"/>.</para>
		/// </remarks>
		Vector3 getClientLocation() const {
			Vector3 result;
			sampgdk::GetPlayerPos(this->getIndex(), &result.x, &result.y, &result.z);
			return result;
		}

		const std::size_t	m_index;			/// Player in-game index.
		std::string			m_name;				/// Player in-game nickname.

		bool				m_spawned;			/// Determines whether player is spawned.
		Vector3				m_lastLocation;		/// Last set location.
		
		// Player statistics.
		
		std::int32_t		m_score;			/// Player's in-game score.
		std::int32_t		m_cash;				/// Player's in-game cash.

		// Player condition.
		float				m_health;			/// Player's in-game health.
		float				m_armour;			/// Player's in-game armour.
	};
}