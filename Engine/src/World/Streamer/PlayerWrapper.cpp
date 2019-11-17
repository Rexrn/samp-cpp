#include SAMPCPP_PCH

#include <SAMPCpp/World/Streamer/PlayerWrapper.hpp>
#include <SAMPCpp/Server/GameMode.hpp>

namespace samp_cpp::default_streamer
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
void PlayerWrapper::whenPlacementChanges(ActorPlacement const& prevPlacement_, ActorPlacement const& newPlacement_)
{
	GameMode->streamer->whenPlayerPlacementChanges(*m_player, prevPlacement_, newPlacement_);
}

}
