/**
 * Header: PlayerPool.hpp
 * Author: Pawe³ Syska aka RazzorFlame.
 * Description:
 * Implements class manipulating players and agent used to process certain server events.
**/

#pragma once

// AGDK includes
#include "../Player/Player.hpp"
#include "Misc/Math.hpp"			// agdk::Vector3, length classes

// STD includes
#include <vector>
#include <memory>
#include <string_view>

namespace agdk
{		
	class PlayerPool;

	/// <summary>
	/// Agent used to manipulate player pool by <see cref="IGameMode"/>
	/// </summary>
	class PlayerPoolAgent final
	{
	public:		
		/// <summary>
		/// Copy constructor. It is deleted.
		/// </summary>
		PlayerPoolAgent(const PlayerPoolAgent &) = delete;
		
		/// IGameMode only can create PlayerPoolAgent.
		friend class IGameMode;

	private:		
		/// <summary>
		/// Prevents a default instance of the <see cref="PlayerPoolAgent"/> class from being created.
		/// </summary>
		PlayerPoolAgent() = delete;

		/// <summary>
		/// Constructor. Only IGameMode is allowed to create instance of this class.
		/// </summary>
		/// <param name="playerPool_">The player pool.</param>
		PlayerPoolAgent(PlayerPool &playerPool_);
		
		/// <summary>
		/// Adds player to player pool.
		/// </summary>
		/// <param name="player_">The player.</param>
		/// <remarks>
		/// <para>Player was already created before this event was fired.
		/// This is because IGameMode is responsive for providing player instances.
		/// </para>
		/// </remarks>
		void eventPlayerConnect(std::shared_ptr<Player> &&player_);
		
		/// <summary>
		/// Removes player from player pool.
		/// </summary>
		/// <param name="playerIndex_">Index of the player.</param>
		/// <remarks>
		/// <para>Only index is passed because it is faster to randomly access vector element with its index than searching for player pointer.</para>
		/// </remarks>
		void eventPlayerDisconnect(const std::size_t playerIndex_);
		
		/// <summary>
		/// The player pool reference.
		/// </summary>
		PlayerPool &m_playerPool;
	};

	/// <summary>
	/// Stores every player in game.
	/// </summary>
	class PlayerPool final
	{
	public:
		using PoolType			= std::vector< std::shared_ptr< Player > >;
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
		Player* get(const std::size_t playerIndex_) const;
		
		
		/// <summary>
		/// Finds player with the specified function.
		/// </summary>
		/// <param name="func_">The function.</param>
		/// <returns>Player found with specified function. May be null pointer.</returns>
		template <typename _Func>
		Player* find(_Func func_) const
		{
			auto it = std::find_if(m_connectedPlayers.begin(), m_connectedPlayers.end(), func_);
			if (it != m_connectedPlayers.end())
				return it->get();
			return nullptr;
		}

		/// <summary>
		/// Finds the everyone in radius from specified location.
		/// </summary>
		/// <param name="location_">The location.</param>
		/// <param name="radius">The radius.</param>
		/// <returns>Vector of players in radius from specified location.</returns>
		RawPoolType findEveryoneInRadius(const Vector3 location_, const Meters radius) const;
		
		/// <summary>
		/// Finds the nearest player within the radius from specified location.
		/// </summary>
		/// <param name="location_">The location.</param>
		/// <param name="radius_">The radius.</param>
		/// <returns>Nearest player within the radius from specified location. May be null pointer.</returns>
		Player* findNearest(const Vector3 location_, const Meters radius) const;

		/// <summary>
		/// Finds the nearest player within the radius from specified player.
		/// </summary>
		/// <param name="player_">The location.</param>
		/// <param name="radius_">The radius.</param>
		/// <returns>Nearest player within the radius from specified location. May be null pointer.</returns>
		Player* findNearest(const Player *const player_, const Meters radius_) const;

		/// <summary>
		/// Finds the player by name.
		/// </summary>
		/// <param name="name_">Name of the player.</param>
		/// <param name="caseSensitive_">Case sensitive.</param>
		/// <returns>Player found by name. May be null pointer.</returns>
		Player* findByName(const std::string_view name_, const bool caseSensitive_ = true) const;
	
		/// <summary>
		/// Finds player by name or index stored in string.
		/// </summary>
		/// <param name="nameOrIndex">Name or index stored in string.</param>
		/// <param name="caseSensitive_">Case sensitive.</param>
		/// <returns>Player found by name or index. May be null pointer.</returns>
		Player* findByNameOrIndex(const std::string_view nameOrIndex_, const bool caseSensitive_ = true) const;

		/// <summary>
		/// Finds player by name or index stored in string (picks best match).
		/// </summary>
		/// <param name="nameOrIndex_">Name or index stored in string</param>
		/// <param name="minimalScore_">The minimal score (number of characters in sequence).</param>
		/// <returns>Player found by name or index. May be null pointer.</returns>
		/// <remarks>
		/// <para>
		/// Parameter "minimalScore_" is preventing from picking random players that matches only with few letters.
		///	Case sensitivity is turned off!
		///	This is because this function should be used as easier way to find players.
		///	Be careful though - administrative operations like setting player's rank shouldn't be
		///	implemented using this function.It may cause unwanted players to get
		///	high ranks and is generally dangerous. Can be freely used in f.e. command: /goto [player name / id]
		/// </para>
		/// </remarks>
		Player* findBestMatch(const std::string_view nameOrIndex_, const std::size_t minimalScore_ = 2) const;

		/// <summary>
		/// Gets the player pool (of raw pointers).
		/// </summary>
		/// <returns>Pool (std::vector) containing every player.</returns>
		auto getPool() const { return m_connectedPlayers; }

		/// PlayerPoolAgent have access to some private members.
		friend class PlayerPoolAgent;
	private:

		/// <summary>
		/// Agent method: adds player to the pool. See also: <see cref="PlayerPoolAgent::eventPlayerConnect" />
		/// </summary>
		/// <param name="agent_">The agent.</param>
		/// <param name="player_">The player.</param>
		void agentAddPlayer(PlayerPoolAgent &agent_, std::shared_ptr<Player> &&player_);
		
		/// <summary>
		/// Agent method: removes player from the pool. See also: <see cref="PlayerPoolAgent::eventPlayerDisconnect" />
		/// </summary>
		/// <param name="agent_">The agent.</param>
		/// <param name="playerIndex_">Index of the player.</param>
		void agentRemovePlayer(PlayerPoolAgent &agent_, const std::size_t playerIndex_);

		// Private members
		
		PoolType			m_playerPool;		/// Store players in vector of shared pointers.
		RawPoolType			m_playerRawPool;	/// Store raw pointers in this vector.
		RawPoolType			m_connectedPlayers;	/// Store every connected player in this vector.

	public:
		const std::size_t	maxPlayers;
	};

}

