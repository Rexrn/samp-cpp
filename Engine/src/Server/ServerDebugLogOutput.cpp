#include SAMPCPP_PCH

#include <SAMPCpp/Server/ServerDebugLogOutput.hpp>

#include <SAMPCpp/Server/GameMode.hpp>

#include <SAMPCpp/Core/TextInc.hpp>

namespace samp_cpp
{

#ifdef DEBUG

///////////////////////////////////////////////////////////
ServerDebugLogOutput::ServerDebugLogOutput(IGameMode & gameMode_)
	: IGameModeChild(gameMode_)
{		
}

///////////////////////////////////////////////////////////
void ServerDebugLogOutput::push(LogMessage messageType_, std::string message_)
{
	auto& gameMode = this->getGameMode();
	if (auto chat = gameMode.chat.get())
	{
		std::string prefix;
		switch(messageType_)
		{
			case LogMessage::Info: prefix = "INFO"; break;
			case LogMessage::Warning: prefix = "WARNING"; break;
			case LogMessage::Error: prefix = "ERROR"; break;
			case LogMessage::FatalError: prefix = "FATAL ERROR"; break;
		}

		message_ = text::format("{2}[DEBUG LOG | {0}]: {3}{1}", prefix, message_, colors::Lightslategray, colors::Lightgray);

		auto const& playerPool = this->getGameMode().players.getPool();
		for(auto p : playerPool)
		{
			if (p->receivesServerDebugLog()) {
				chat->messagePlayer(*p, message_);
			}
		}
	}
		
}

#endif

}