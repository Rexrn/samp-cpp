#include SAMPCPP_PCH

#include <SAMPCpp/Server/CommandHandler.hpp>
#include <SAMPCpp/Core/Text/ASCII.hpp>

#include <SAMPCpp/Server/Server.hpp>
#include <SAMPCpp/Core/Text/StreamAlgorithm.hpp>

#include <SAMPCpp/Server/GameMode.hpp>

namespace samp_cpp
{
//////////////////////////////////////////////////////////////////////////////
bool DefaultCommandHandler::exists(std::string_view const input_) const
{
	auto lowerCaseInput = text::toLower(std::string{ input_ });

	auto it = std::find_if(_commandPool.begin(), _commandPool.end(),
			[&lowerCaseInput](UniquePtr<Command> const & cmd_)
			{
				return cmd_->matchesInput(lowerCaseInput);
			}
		);

	return it != _commandPool.end();
}

//////////////////////////////////////////////////////////////////////////////
Command* DefaultCommandHandler::find(std::string_view const input_)
{
	auto lowerCaseInput = text::toLower(std::string{ input_ });

	auto it = std::find_if(_commandPool.begin(), _commandPool.end(),
		[&lowerCaseInput](UniquePtr<Command> const & cmd_)
		{
			return cmd_->matchesInput(lowerCaseInput);
		});

	if (it != _commandPool.end()) {
		return it->get();
	}
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////////
bool DefaultCommandHandler::remove(Command & command_)
{
	auto it = std::find_if(_commandPool.begin(), _commandPool.end(),
		[&command_](UniquePtr<Command> const & cmd_)
		{
			return cmd_.get() == &command_;
		});

	if (it != _commandPool.end())
	{
		_commandPool.erase(it);
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////
void DefaultCommandHandler::whenPlayerSendsCommandText(Player & player_, std::string_view commandText_)
{
	std::istringstream stream{ std::string{commandText_} };
	if (stream >> text::skipIf<char, '/'>)
	{
		std::string input;
		if (stream >> input)
		{
			std::string params;
			std::getline(stream, params);

			if (auto command = this->find(input))
				command->invoke(CommandInput{ player_, input, params });
			else if (onInvalidCommand)
				onInvalidCommand(player_, commandText_);
		}
	}
}

} // namespace agdk