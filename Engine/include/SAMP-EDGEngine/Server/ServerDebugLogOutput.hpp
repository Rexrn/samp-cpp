#pragma once

#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/Core/BasicInterfaces/LogOutput.hpp>
#include <SAMP-EDGEngine/Core/Log.hpp>
#include <SAMP-EDGEngine/Server/GameModeChild.hpp>

namespace samp_cpp
{

#ifdef DEBUG

class ServerDebugLogOutput
	:
	public ILogOutput,
	public IGameModeChild
{
public:
	ServerDebugLogOutput(IGameMode & gameMode_);

	virtual void push(LogMessage messageType_, std::string message_) override;
};

#endif

}