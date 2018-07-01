#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/Server/CommandManager.hpp>
#include <AdvancedGDK/Core/Text/ASCII.hpp>

#include <AdvancedGDK/Server/Server.hpp>
#include <AdvancedGDK/Core/Text/StreamAlgorithm.hpp>

namespace agdk
{
//////////////////////////////////////////////////////////////////////////////
CommandManager::CommandManager()
{
	Server->Events.PlayerSendsCommandText += { *this, &CommandManager::whenPlayerSendsCommandText };
}

//////////////////////////////////////////////////////////////////////////////
Command& CommandManager::add(UniquePtr<Command>&& command_)
{
	Command& ref = *command_;
	m_commands.push_back( std::forward< UniquePtr<Command> >(command_) );
	return ref;
}

//////////////////////////////////////////////////////////////////////////////
bool CommandManager::exists(std::string_view const input_) const
{
	auto lowerCaseInput = text::ascii::toLower(std::string{ input_ });

	auto it = std::find_if(m_commands.begin(), m_commands.end(),
		[&lowerCaseInput](UniquePtr<Command> const & cmd_)
		{
			return cmd_->matchesInput(lowerCaseInput);
		});

	return it != m_commands.end();
}

//////////////////////////////////////////////////////////////////////////////
Command* CommandManager::find(std::string_view const input_)
{
	auto lowerCaseInput = text::ascii::toLower(std::string{ input_ });

	auto it = std::find_if(m_commands.begin(), m_commands.end(),
		[&lowerCaseInput](UniquePtr<Command> const & cmd_)
		{
			return cmd_->matchesInput(lowerCaseInput);
		});

	if (it != m_commands.end()) {
		return it->get();
	}
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////////
bool CommandManager::remove(Command & command_)
{
	auto it = std::find_if(m_commands.begin(), m_commands.end(),
		[&command_](UniquePtr<Command> const & cmd_)
		{
			return cmd_.get() == &command_;
		});

	if (it != m_commands.end())
	{
		m_commands.erase(it);
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////
void CommandManager::whenPlayerSendsCommandText(Player & player_, std::string_view commandText_)
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
			{
				command->invoke(CommandInput{ player_, input, params });
			}
		}
	}
}

} // namespace agdk