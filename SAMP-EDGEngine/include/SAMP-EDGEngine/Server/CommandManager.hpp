#pragma once

#include SAMP_EDGENGINE_PCH

#include <SAMP-EDGEngine/Server/Command.hpp>

#include <SAMP-EDGEngine/Core/BasicInterfaces/NonCopyable.hpp>
#include <SAMP-EDGEngine/Core/Events.hpp>
#include <SAMP-EDGEngine/Core/Pointers.hpp>

namespace agdk
{
/// <summary>
/// Class used to manage commands.
/// </summary>
class CommandManager final
	: public INonCopyable, public IEventReceiver
{
public:

	/// <summary>
	/// Adds the specified command to the pool.
	/// </summary>
	/// <param name="command_">The command.</param>
	Command& add(UniquePtr<Command> &&command_);

	/// <summary>
	/// Adds the specified command to the pool (constructs it from given parameters).
	/// </summary>
	/// <param name="command_">The command.</param>
	template <typename TCommandType, typename... TArgs>
	TCommandType& construct(TArgs&&... args_)
	{
		return static_cast<TCommandType&>( this->add(std::make_unique<TCommandType>(std::forward<TArgs>(args_)...)) );
	}

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
	CommandManager();
	
	/// <summary>
	/// Called when player sends command. Invokes specified command.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <param name="commandText_">The command text.</param>
	void whenPlayerSendsCommandText(Player & player_, std::string_view commandText_);

	///	Vector of all commands.
	std::vector<UniquePtr<Command>> m_commands;
};
}
