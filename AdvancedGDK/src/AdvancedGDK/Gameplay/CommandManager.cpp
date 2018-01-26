#include "stdafx.h"

#include <AdvancedGDK/Gameplay/CommandManager.hpp>
#include <AdvancedGDK/Misc/String.hpp>

namespace agdk
{
//////////////////////////////////////////////////////////////////////////////
void CommandManager::add(std::unique_ptr<Command>&& command_)
{
	m_commands.push_back( std::forward< std::unique_ptr<Command> >(command_) );
}

//////////////////////////////////////////////////////////////////////////////
bool CommandManager::exists(std::string_view const input_) const
{
	auto lowerCaseInput = StringHelper::toLower(std::string{ input_ });

	auto it = std::find_if(m_commands.begin(), m_commands.end(),
		[&lowerCaseInput](std::unique_ptr<Command> const & cmd_) {
		return cmd_->matchesInput(lowerCaseInput);
	});

	return it != m_commands.end();
}

//////////////////////////////////////////////////////////////////////////////
Command* CommandManager::find(std::string_view const input_)
{
	auto lowerCaseInput = StringHelper::toLower(std::string{ input_ });

	auto it = std::find_if(m_commands.begin(), m_commands.end(),
		[&lowerCaseInput](std::unique_ptr<Command> const & cmd_) {
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
		[&command_](std::unique_ptr<Command> const & cmd_) {
		return cmd_.get() == &command_;
	});
	if (it != m_commands.end()) {
		m_commands.erase(it);
		return true;
	}
	return false;
}
}