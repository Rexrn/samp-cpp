#pragma once

#include SAMPCPP_PCH

namespace samp_cpp 
{

class IGameMode;
class IGameModeChild
{
public:
	IGameModeChild(IGameMode & gameMode_)
		: m_gameMode{ gameMode_ } 
	{
	}

	IGameMode& getGameMode() const { 
		return m_gameMode;
	}
private:
	IGameMode& m_gameMode;
};

}