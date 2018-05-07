#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/Streamer/PlayerWrapper.hpp>

namespace agdk::default_streamer
{

/////////////////////////////////////////////////////////////
PlayerWrapper::PlayerWrapper()
	: m_player{ nullptr }
{
}

/////////////////////////////////////////////////////////////
PlayerWrapper::PlayerWrapper(Player& player_)
	: m_player{ &player_ }
{
}

/////////////////////////////////////////////////////////////
void PlayerWrapper::setPlayer(Player& player_)
{
	m_player = &player_;
}

/////////////////////////////////////////////////////////////
void PlayerWrapper::whenPlacementChanges(ActorPlacement const& prevPlacement_, ActorPlacement const& newPlacement_)
{
	// TODO: implement this:
	// Find a way to notify streamer without breaking SOLID.
	// Possibly by interface (like the abstraction layers work).
}

}
