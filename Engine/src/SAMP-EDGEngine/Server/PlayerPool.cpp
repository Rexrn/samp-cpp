#include "EnginePCH.hpp" // PCH

// Custom headers:
#include <SAMP-EDGEngine/Server/PlayerPool.hpp>
#include <SAMP-EDGEngine/Core/Text/ASCII.hpp>
#include <SAMP-EDGEngine/Core/Pointers.hpp>


namespace samp_edgengine
{

//////////////////////////////////////////////////////////////////////////////
PlayerPool::PlayerPool()
	: maxPlayers( static_cast<std::size_t>(sampgdk_GetMaxPlayers()) )
{
	m_playerPool.resize(maxPlayers);
	m_playerRawPool.resize(maxPlayers, nullptr);
	m_connectedPlayers.reserve(maxPlayers);
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
PlayerPool::RawPoolType PlayerPool::findEveryoneInRadius(math::Vector3f const location_, math::Meters const radius_)
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
Player * PlayerPool::findNearest(math::Vector3f const location_, math::Meters const radius_)
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
Player * PlayerPool::findNearest(Player const * const player_, math::Meters const radius_)
{
	// Check if there are at least two Players at the server.
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
			if(caseSensitive_)
				return text::ascii::equal(name_, player_->getName());
			else
				return text::ascii::equal<text::CaseInsensitive>(name_, player_->getName());
		});
}

//////////////////////////////////////////////////////////////////////////////
Player * PlayerPool::findByNameOrIndex(std::string_view const nameOrIndex_, bool const caseSensitive_)
{
	Player *result = nullptr;

	// At first we want to examine player index.
	if (auto index = text::ascii::convert<std::size_t>(nameOrIndex_);
		index.has_value())
	{
		result = this->get(index.value());
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
			auto const [itMin, itMax] = text::ascii::searchWithIncomplete<text::CaseInsensitive>(player->getName(), nameOrIndex_);
			auto const score = itMax - itMin;
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
Player& PlayerPool::whenPlayerConnectsEx(SharedPtr<Player>&& player_)
{
	auto index = player_->getIndex();

	m_playerPool[index] = std::forward< SharedPtr<Player> >(player_);
	// Do not use player_ from now.
	m_playerRawPool[index] = m_playerPool[index].get();
		
	return *m_connectedPlayers.emplace_back(m_playerRawPool[index]);
}

//////////////////////////////////////////////////////////////////////////////
void PlayerPool::whenPlayerDisconnectsEx(std::size_t const playerIndex_)
{
	// Remove from connected Players.
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
