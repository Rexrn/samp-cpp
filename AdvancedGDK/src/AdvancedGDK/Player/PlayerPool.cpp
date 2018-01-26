#include "stdafx.h" // PCH

// Custom headers:
#include <AdvancedGDK/Player/PlayerPool.hpp>
#include <AdvancedGDK/SampGDK.hpp>
#include <AdvancedGDK/Misc/String.hpp>


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
		m_playerPool.agentAddPlayer(std::forward< std::shared_ptr<Player> >(player_));
	}

	//////////////////////////////////////////////////////////////////////////////
	void PlayerPoolAgent::eventPlayerDisconnect(std::size_t const playerIndex_)
	{
		m_playerPool.agentRemovePlayer(playerIndex_);
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
	Player * PlayerPool::get(std::size_t const playerIndex_) const
	{
		return m_playerRawPool[playerIndex_];
	}

	//////////////////////////////////////////////////////////////////////////////
	PlayerPool::RawPoolType PlayerPool::findEveryoneInRadius(Vector3 const location_, Meters const radius_)
	{
		// Check if there is any player on the server.
		if (m_connectedPlayers.empty())
			return {};


		auto result = RawPoolType{};
		// Reserve memory for faster calculation
		result.reserve(m_connectedPlayers.size());

		for (const auto &player : m_connectedPlayers)
		{
			if(player->getDistanceTo(location_) <= radius_)
				result.push_back(player);
		}

		// Cut reserved memory
		result.resize(result.size());
		return result;
	}

	//////////////////////////////////////////////////////////////////////////////
	Player * PlayerPool::findNearest(Vector3 const location_, Meters const radius_)
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
	Player * PlayerPool::findNearest(Player const * const player_, Meters const radius_)
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
	Player * PlayerPool::findByName(std::string_view const name_, bool const caseSensitive_)
	{
		return this->find(
			[&name_, &caseSensitive_](Player *const player_)
		{
			return StringHelper::equals(name_, player_->getName(), false);
		});
	}

	//////////////////////////////////////////////////////////////////////////////
	Player * PlayerPool::findByNameOrIndex(std::string_view const nameOrIndex_, bool const caseSensitive_)
	{
		Player *result = nullptr;

		// At first we want to examine player index.
		if (StringHelper::storesInteger(nameOrIndex_))
		{
			// When Visual Studio will add support to std::from_chars, you can switch this macro.
#ifdef _AGDK_FS_STRINGHELPER_TO_CXX17FROMCHARS
			std::size_t index = StringHelper::to<std::size_t>(nameOrIndex_);
#else
			std::size_t index = StringHelper::to<std::size_t>(std::string{ nameOrIndex_ });
#endif
			result = this->get(index);
		}
		if (!result) // Then try to find by name.
			result = this->findByName(nameOrIndex_, caseSensitive_);
		return result;
	}

	//////////////////////////////////////////////////////////////////////////////
	Player * PlayerPool::findBestMatch(std::string_view const nameOrIndex_, std::size_t const minimalScore_)
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
	void PlayerPool::agentAddPlayer(std::shared_ptr<Player>&& player_)
	{
		auto index		= player_->getIndex();
		auto playerPtr	= player_.get();

		m_playerPool[index] = std::forward< std::shared_ptr<Player> >(player_);
		// Do not use player_ from now.
		m_playerRawPool[index] = playerPtr;
		m_connectedPlayers.push_back(playerPtr);
	}

	//////////////////////////////////////////////////////////////////////////////
	void PlayerPool::agentRemovePlayer(std::size_t const playerIndex_)
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