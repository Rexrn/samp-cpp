#include "stdafx.h"
#include <Player/PlayerPool.hpp>

#include <SampGDK.hpp>

// AGDK headers
#include <Misc/String.hpp>

// STD headers
#include <algorithm>

namespace agdk
{
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////	class PlayerPoolAgent
	//////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////
	PlayerPoolAgent::PlayerPoolAgent(PlayerPool & playerPool_)
		: m_playerPool(playerPool_)
	{
	}

	//////////////////////////////////////////////////////////////////////////////
	void PlayerPoolAgent::eventPlayerConnect(std::shared_ptr<Player>&& player_)
	{
		m_playerPool.agentAddPlayer(*this, std::forward< std::shared_ptr<Player> >(player_));
	}

	//////////////////////////////////////////////////////////////////////////////
	void PlayerPoolAgent::eventPlayerDisconnect(const std::size_t playerIndex_)
	{
		m_playerPool.agentRemovePlayer(*this, playerIndex_);
	}

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////	class PlayerPool
	//////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////
	PlayerPool::PlayerPool()
		: maxPlayers( static_cast<std::size_t>(sampgdk::GetMaxPlayers()) )
	{
		m_playerPool.resize(maxPlayers);
		m_playerRawPool.resize(maxPlayers, nullptr);
	}

	//////////////////////////////////////////////////////////////////////////////
	PlayerPool::~PlayerPool()
	{
	}

	//////////////////////////////////////////////////////////////////////////////
	Player * PlayerPool::get(const std::size_t playerIndex_) const
	{
		return m_playerRawPool[playerIndex_];
	}

	//////////////////////////////////////////////////////////////////////////////
	PlayerPool::RawPoolType PlayerPool::findEveryoneInRadius(const Vector3 location_, const Meters radius) const
	{
		// Check if there is any player on the server.
		if (m_connectedPlayers.empty())
			return {};


		auto result = RawPoolType{};
		// Reserve memory for faster calculation
		result.reserve(m_connectedPlayers.size());

		for (const auto &player : m_connectedPlayers)
		{
			if(player->getDistanceTo(location_) <= radius)
				result.push_back(player);
		}

		// Cut reserved memory
		result.resize(result.size());
		return result;
	}

	//////////////////////////////////////////////////////////////////////////////
	Player * PlayerPool::findNearest(const Vector3 location_, const Meters radius_) const
	{
		// Check if there is any player on the server.
		if (m_connectedPlayers.empty())
			return nullptr;
		
		auto it = std::min_element(m_connectedPlayers.begin(), m_connectedPlayers.end(),
			[&location_](Player *const lhs, Player *const rhs)
		{
			return lhs->getDistanceTo(location_) < rhs->getDistanceTo(location_);
		});

		// Make sure that nearest player is within radius; otherwise return null pointer.
		return ((*it)->getDistanceTo(location_) <= radius_ ? *it : nullptr);
	}

	//////////////////////////////////////////////////////////////////////////////
	Player * PlayerPool::findNearest(const Player * const player_, const Meters radius_) const
	{
		// Check if there are at least two players at the server.
		if (m_connectedPlayers.size() < 2)
			return nullptr;

		// Cache the location.
		const auto location = player_->getLocation();

		auto it = std::min_element(m_connectedPlayers.begin(), m_connectedPlayers.end(),
			[player_, &location](Player *const lhs, Player *const rhs)
		{
			// Make sure that player_ will always be at the end of the list.
			if (lhs == player_)
				return false;
			if (rhs == player_)
				return true;

			return lhs->getDistanceTo(location) < rhs->getDistanceTo(location);
		});

		// Make sure that nearest player is within radius; otherwise return null pointer.
		return ((*it)->getDistanceTo(location) <= radius_ ? *it : nullptr);
	}

	//////////////////////////////////////////////////////////////////////////////
	Player * PlayerPool::findByName(const std::string_view name_, const bool caseSensitive_) const
	{
		return this->find(
			[&name_, &caseSensitive_](Player *const player)
		{
			return StringHelper::equals(name_, player->getName(), false);
		});
	}

	//////////////////////////////////////////////////////////////////////////////
	Player * PlayerPool::findByNameOrIndex(const std::string_view nameOrIndex_, const bool caseSensitive_) const
	{
		Player *result = nullptr;

		// At first we want to examine player index.
		if (StringHelper::storesInteger(nameOrIndex_))
		{
			std::size_t index = StringHelper::to<std::size_t>(nameOrIndex_);
			result = this->get(index);
		}
		if (!result) // Then try to find by name.
			result = this->findByName(nameOrIndex_, caseSensitive_);
		return result;
	}

	//////////////////////////////////////////////////////////////////////////////
	Player * PlayerPool::findBestMatch(const std::string_view nameOrIndex_, const std::size_t minimalScore_) const
	{
		// Try to find by complete name or index.
		Player* result = this->findByNameOrIndex(nameOrIndex_, false);

		// Check if lookup failed and try to take best match.
		if (!result)
		{
			std::size_t maxScore = 0;
			for (const auto &player : m_connectedPlayers)
			{
				auto score = StringHelper::maxSequenceLength(player->getName(), nameOrIndex_, false);
				if (score > maxScore && score >= minimalScore_)
				{
					result = player;
					maxScore = score;
				}
			}
		}
		return result;
	}

	//////////////////////////////////////////////////////////////////////////////
	void PlayerPool::agentAddPlayer(PlayerPoolAgent & agent_, std::shared_ptr<Player>&& player_)
	{
		auto index		= player_->getIndex();
		auto playerPtr	= player_.get();

		m_playerPool[index] = std::forward< std::shared_ptr<Player> >(player_);
		// Do not use player_ from now.
		m_playerRawPool[index] = playerPtr;
		m_connectedPlayers.push_back(playerPtr);
	}

	//////////////////////////////////////////////////////////////////////////////
	void PlayerPool::agentRemovePlayer(PlayerPoolAgent & agent_, const std::size_t playerIndex_)
	{
		// Remove from connected players.
		{
			auto it = std::find_if(m_connectedPlayers.begin(), m_connectedPlayers.end(),
				[playerIndex_](Player *const element) { return element->getIndex() == playerIndex_; });
			m_connectedPlayers.erase(it);
		}

		// Reset raw pointer.
		m_playerRawPool[playerIndex_] = nullptr;
		// Reset the smart pointer.
		m_playerPool[playerIndex_].reset();
	}
}