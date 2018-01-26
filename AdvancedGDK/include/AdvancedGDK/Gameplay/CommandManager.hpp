#pragma once

#include "../../../stdafx.h"

#include <AdvancedGDK/Gameplay/Command.hpp>

namespace agdk
{
/// <summary>
/// Class used to manage commands.
/// </summary>
class CommandManager
{
public:
	/// <summary>
	/// Prevents copying instances of <see cref="CommandManager"/> class.
	/// </summary>
	/// <param name="other_">The other instance.</param>
	CommandManager(CommandManager const &other_) = delete;

	/// <summary>
	/// Adds the specified command to the pool.
	/// </summary>
	/// <param name="command_">The command.</param>
	void add(std::unique_ptr<Command> &&command_);

	/// <summary>
	/// Checks whether command with specified input exists in the pool.
	/// </summary>
	/// <param name="input_">The input.</param>
	/// <returns>
	///		<c>true</c> if command exists; otherwise <c>false</c>
	/// </returns>
	bool exists(std::string_view const input_) const;

	/// <summary>
	/// Finds command with specified input.
	/// </summary>
	/// <param name="input_">The input.</param>
	/// <returns>Pointer to command. <c>nullptr</c> if not found.</returns>
	Command* find(std::string_view const input_);

	/// <summary>
	/// Removes the specified command.
	/// </summary>
	/// <param name="command_">The command.</param>
	/// <returns>
	///		<c>true</c> if removed; otherwise <c>false</c>.
	/// </returns>
	bool remove(Command & command_);

	/// <summary>
	/// Returns cref to command pool.
	/// </summary>
	/// <returns>cref to command pool</returns>
	auto const & getAll() const {
		return m_commands;
	}

	//	Declare friendship with ServerLogic class.
	friend class IGameMode;
private:
	/// <summary>
	/// Initializes new instance of a <see cref="CommandManager"/> class.
	/// </summary>
	CommandManager() = default;

	///	Vector of all commands.
	std::vector<std::unique_ptr<Command>> m_commands;
};
}
