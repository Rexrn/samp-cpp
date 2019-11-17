#pragma once

#include SAMPCPP_PCH

#include <SAMPCpp/Core/BasicInterfaces/LogOutput.hpp>
#include <SAMPCpp/Core/Log.hpp>
#include <SAMPCpp/Server/GameModeChild.hpp>

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