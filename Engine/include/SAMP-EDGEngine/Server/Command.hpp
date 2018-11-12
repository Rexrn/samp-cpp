#pragma once

#include <SAMP-EDGEngine/Core/Text/ASCII.hpp>
#include <SAMP-EDGEngine/Server/Teleport.hpp>

namespace samp_edgengine
{
using CmdInvocations = std::vector< std::string >;

class Player;
	
/// <summary>
/// Class that is passed to every command.
/// </summary>
struct CommandInput
{		
	/// <summary>
	/// Constructs <see cref="CommandInput"/> from passed parameters.
	/// </summary>
	/// <param name="target_">The target player (caller).</param>
	/// <param name="input_">The input word.</param>
	/// <param name="params_">Rest of the parameters.</param>
	CommandInput(Player & target_, std::string const & input_, std::string const & params_);
	
	/// <summary>
	/// Splits the parameters by space character.
	/// </summary>
	/// <returns>Vector of splitted parameters</returns>
	std::vector<std::string> splitParams() const;

	/// Caller
	Player&			target;
	/// String that contains first word after '/' (slash) character.
	std::string		input;
	/// String that contains everything after `input` word.
	std::string		params;
};


/// <summary>
/// Class representing command.
/// It is used to create command passed to Command Manager.
/// </summary>
struct Command
{
	/// <summary>
	/// Constructs <see cref="Command"/> from passed parameters.
	/// </summary>
	/// <param name="possibleInputs_">The possible inputs.</param>
	Command(std::vector<std::string> const & possibleInputs_)
		: m_possibleInputs{ possibleInputs_ }
	{
	}

	/// <summary>
	/// Checks if `input` matches possible input list.
	/// </summary>
	/// <param name="input_">The input command.</param>
	/// <returns></returns>
	bool matchesInput(std::string_view const input_) const;
		
	/// <summary>
	/// Returns the possible inputs.
	/// </summary>
	/// <returns>cref to possible inputs vector</returns>
	auto const& getPossibleInputs() const {
		return m_possibleInputs;
	}

	friend class CommandManager;
protected:
	/// <summary>
	/// Invokes command.
	/// </summary>
	/// <param name="input_">The input.</param>
	virtual void invoke(CommandInput input_) = 0;

	///	Vector of possible inputs.
	std::vector<std::string> m_possibleInputs;
};

/// <summary>
/// Class representing teleport command.
/// </summary>
/// <seealso cref="Command" />
class ProcedureCommand
	: public Command
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="TeleportCommand"/> class from passed parameters.
	/// </summary>
	/// <param name="inputs_">The inputs.</param>
	/// <param name="teleport_">The teleport.</param>
	template <typename _Func>
	ProcedureCommand(std::vector<std::string> inputs_, _Func function_)
		: Command{ inputs_ }, m_function{ function_ }
	{
	}

	friend class CommandManager;
protected:
	/// <summary>
	/// Invokes command.
	/// </summary>
	/// <param name="target">The target player.</param>
	/// <param name="input">The input.</param>
	/// <param name="paramsString">The parameters string.</param>
	virtual void invoke(CommandInput input_) override;

	///	Pointer to command function.
	std::function<void(CommandInput)>	m_function;
};

/// <summary>
/// Class representing teleport command.
/// </summary>
/// <seealso cref="Command" />
class TeleportCommand
	: public Command
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="TeleportCommand"/> class from passed parameters.
	/// </summary>
	/// <param name="inputs_">The inputs.</param>
	/// <param name="teleport_">The teleport.</param>
	TeleportCommand(std::vector<std::string> inputs_, Teleport const & teleport_)
		: Command{ inputs_ }, m_teleport{ teleport_ }
	{
	}

	friend class CommandManager;
protected:
	/// <summary>
	/// Invokes command.
	/// </summary>
	/// <param name="target">The target player.</param>
	/// <param name="input">The input.</param>
	/// <param name="paramsString">The parameters string.</param>
	virtual void invoke(CommandInput input_) override;

	Teleport m_teleport;
};
}
