#pragma once
#include SAMPEDGENGINE_PCH



#include <SAMP-EDGEngine/Server/Command.hpp>

#include <SAMP-EDGEngine/Core/BasicInterfaces/NonCopyable.hpp>
#include <SAMP-EDGEngine/Server/GameModeChild.hpp>
#include <SAMP-EDGEngine/Core/Events.hpp>
#include <SAMP-EDGEngine/Core/Pointers.hpp>

namespace samp_cpp
{

/// <summary>
/// Class used to manage commands.
/// </summary>
class ICommandHandler
	: public IGameModeChild, public INonCopyable, public IEventReceiver
{
public:
	using IGameModeChild::IGameModeChild;

	/// <summary>
	/// Called when player sends command.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <param name="commandText_">The command text.</param>
	virtual void whenPlayerSendsCommandText(Player & player_, std::string_view commandText_) = 0;
};

/// <summary>
/// Default implementation of the command handler.
/// </summary>
class DefaultCommandHandler
	: public ICommandHandler
{
public:
	using ICommandHandler::ICommandHandler;

	/// <summary>
	/// Adds the specified command to the pool.
	/// </summary>
	/// <param name="command_">The command.</param>
	template <typename TCommandType,
		typename = std::enable_if_t< std::is_base_of_v<Command, TCommandType> > >
	TCommandType& add(TCommandType&& command_)
	{
		_commandPool.push_back( std::make_unique<TCommandType>( std::forward<TCommandType>(command_) ) );
		return static_cast<TCommandType&>(*_commandPool.back());
	}

	/// <summary>
	/// Adds the specified command to the pool (constructs it from given parameters).
	/// </summary>
	/// <param name="command_">The command.</param>
	template <typename TCommandType, typename... TArgs>
	TCommandType& construct(TArgs&&... args_)
	{
		return this->add<TCommandType>( TCommandType(std::forward<TArgs>(args_)...) );
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
	auto const & getCommandPool() const {
		return _commandPool;
	}

	/// <summary>
	/// Called when player sends command. Invokes specified command.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <param name="commandText_">The command text.</param>
	void whenPlayerSendsCommandText(Player & player_, std::string_view commandText_) override;

	using OnInvalidCommandSignature = void(Player& player_, std::string_view commandText_);

	std::function<OnInvalidCommandSignature> onInvalidCommand;
	
private:
	///	Vector of all commands.
	std::vector<UniquePtr<Command>> _commandPool;
};
}
