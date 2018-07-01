#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/Streamer/PlayerWrapper.hpp>
#include <AdvancedGDK/Server/GameMode.hpp>

namespace agdk::default_streamer
{

/////////////////////////////////////////////////////////////
PlayerWrapper::PlayerWrapper(Player & player_)
	:
	I3DNodePlacementTracker(player_.getPlacement()),
	m_player{ &player_ }
{
	m_player->setPlacementTracker(this);
}

/////////////////////////////////////////////////////////////
void PlayerWrapper::setPlayer(Player & player_)
{
	if (m_player)
		m_player->setPlacementTracker(nullptr);

	m_player = &player_;
	m_player->setPlacementTracker(this);
}

/////////////////////////////////////////////////////////////
void PlayerWrapper::whenPlacementChanges(ActorPlacement const& prevPlacement_, ActorPlacement const& newPlacement_)
{
	GameMode->Streamer->whenPlayerPlacementChanges(*m_player, prevPlacement_, newPlacement_);
}

}
