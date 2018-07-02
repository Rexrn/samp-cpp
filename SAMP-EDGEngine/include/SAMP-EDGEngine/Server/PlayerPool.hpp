// File description:
// Implements class manipulating Players and agent used to process certain server events.
#pragma once

// Precompiled header:
#include SAMP_EDGENGINE_PCH

// Custom includes:
#include <SAMP-EDGEngine/Server/Player.hpp>
#include <SAMP-EDGEngine/Core/Pointers.hpp>

namespace samp_edgengine
{		
class ServerClass;

/// <summary>
/// Stores every player in game.
/// </summary>
class PlayerPool final
{
public:
	using PoolType			= std::vector< SharedPtr< Player > >;
	using RawPoolType		= std::vector< Player * >;

	/// <summary>
	/// Initializes a new instance of the <see cref="PlayerPool"/> class.
	/// </summary>
	PlayerPool();
		
	/// <summary>
	/// Finalizes an instance of the <see cref="PlayerPool"/> class.
	/// </summary>
	~PlayerPool();

	/// <summary>
	/// Gets the specified player using its index.
	/// </summary>
	/// <param name="playerIndex_">Index of the player.</param>
	/// <returns>Pointer to player with specified index.</returns>
	Player* get(std::size_t const playerIndex_) const;
		
	/// <summary>
	/// Gets the specified player using its index.
	/// </summary>
	/// <param name="playerIndex_">Index of the player.</param>
	/// <returns>Pointer to player with specified index.</returns>
	Player* operator[](std::size_t const playerIndex_) const {
		return this->get(playerIndex_);
	}
		
	/// <summary>
	/// Finds player with the specified function.
	/// </summary>
	/// <param name="func_">The function.</param>
	/// <returns>Player found with specified function. May be null pointer.</returns>
	template <typename _Func>
	Player* find(_Func func_)
	{
		auto it = std::find_if(m_connectedPlayers.begin(), m_connectedPlayers.end(), func_);
		if (it != m_connectedPlayers.end())
			return *it;
		return nullptr;
	}

	/// <summary>
	/// Finds the everyone in radius from specified location.
	/// </summary>
	/// <param name="location_">The location.</param>
	/// <param name="radius_">The radius.</param>
	/// <returns>Vector of Players in radius from specified location.</returns>
	RawPoolType findEveryoneInRadius(math::Vector3f const location_, math::Meters const radius_);
		
	/// <summary>
	/// Finds the nearest player within the radius from specified location.
	/// </summary>
	/// <param name="location_">The location.</param>
	/// <param name="radius_">The radius.</param>
	/// <returns>Nearest player within the radius from specified location. May be null pointer.</returns>
	Player* findNearest(math::Vector3f const location_, math::Meters const radius_);

	/// <summary>
	/// Finds the nearest player within the radius from specified player.
	/// </summary>
	/// <param name="player_">The location.</param>
	/// <param name="radius_">The radius.</param>
	/// <returns>Nearest player within the radius from specified location. May be null pointer.</returns>
	Player* findNearest(Player const *const player_, math::Meters const radius_);

	/// <summary>
	/// Finds the player by name.
	/// </summary>
	/// <param name="name_">Name of the player.</param>
	/// <param name="caseSensitive_">Case sensitive.</param>
	/// <returns>Player found by name. May be null pointer.</returns>
	Player* findByName(std::string_view const name_, bool const caseSensitive_ = true);
	
	/// <summary>
	/// Finds player by name or index stored in string.
	/// </summary>
	/// <param name="nameOrIndex">Name or index stored in string.</param>
	/// <param name="caseSensitive_">Case sensitive.</param>
	/// <returns>Player found by name or index. May be null pointer.</returns>
	Player* findByNameOrIndex(std::string_view const nameOrIndex_, bool const caseSensitive_ = true);

	/// <summary>
	/// Finds player by name or index stored in string (picks best match).
	/// </summary>
	/// <param name="nameOrIndex_">Name or index stored in string</param>
	/// <param name="minimalScore_">The minimal score (number of characters in sequence).</param>
	/// <returns>Player found by name or index. May be null pointer.</returns>
	/// <remarks>
	/// <para>
	/// Parameter "minimalScore_" is preventing from picking random Players that matches only with few letters.
	///	Case sensitivity is turned off!
	///	This is because this function should be used as easier way to find Players.
	///	Be careful though - administrative operations like setting player's rank shouldn't be
	///	implemented using this function.It may cause unwanted Players to get
	///	high ranks and is generally dangerous. Can be freely used in f.e. command: /goto [player name / id]
	/// </para>
	/// </remarks>
	Player* findBestMatch(std::string_view const nameOrIndex_, std::size_t const minimalScore_ = 2);

	/// <summary>
	/// Gets the player pool (of raw pointers).
	/// </summary>
	/// <returns>Pool (std::vector) containing every player.</returns>
	auto const & getPool() const {
		return m_connectedPlayers;
	}
	
	/// <summary>
	/// Returns count of online Players.
	/// </summary>
	/// <returns>Count of online Players.</returns>
	std::size_t getCountOfOnlinePlayers() const {
		return m_connectedPlayers.size();
	}
		
	/// <summary>
	/// Determines whether player with the specified index is connected.
	/// </summary>
	/// <param name="playerIndex_">Index of the player.</param>
	/// <returns>
	///		<c>true</c> if player is connected; otherwise <c>false</c>.
	/// </returns>
	auto isConnected(std::size_t const playerIndex_) const {
		return this->get(playerIndex_) != nullptr;
	}

	/// PlayerPoolAgent have access to some private members.
	friend class ServerClass;
private:

	/// <summary>
	/// Called when player connects.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <remarks>
	/// <para>This is an exclusive function, called before any other and with different arguments.</para>
	/// </remarks>
	/// <returns>Reference to added player.</returns>
	Player& whenPlayerConnectsEx(SharedPtr<Player> &&player_);
		
	/// <summary>
	/// Called when player disconnects.
	/// </summary>
	/// <param name="playerIndex_">Index of the player.</param>
	/// <remarks>
	/// <para>This is an exclusive function, called after any other and with different arguments.</para>
	/// </remarks>
	void whenPlayerDisconnectsEx(std::size_t const playerIndex_);

	// Private members
		
	PoolType			m_playerPool;		/// Store Players in vector of shared pointers.
	RawPoolType			m_playerRawPool;	/// Store raw pointers in this vector.
	RawPoolType			m_connectedPlayers;	/// Store every connected player in this vector.

public:
	const std::size_t	maxPlayers;
};

}

