#include "SAMP-EDGEnginePCH.hpp"

#include <SAMP-EDGEngine/Server/Command.hpp>
#include <SAMP-EDGEngine/Server/Server.hpp>

namespace samp_edgengine
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CommandInput::CommandInput(Player & target_, std::string const & input_, std::string const & params_)
	: target{ target_ }, input{ input_ }, params{ params_ }
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::string> CommandInput::splitParams() const
{
	std::istringstream istream{ params };
	return { std::istream_iterator<std::string>{istream}, {} };
}


	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Command::matchesInput(std::string_view const input_) const
{
	return std::find_if(m_possibleInputs.begin(), m_possibleInputs.end(),
		[&input_](std::string const &e_)
		{
			return input_ == e_;
		}) != m_possibleInputs.end();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProcedureCommand::invoke(CommandInput input_)
{
	m_function(input_);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TeleportCommand::invoke(CommandInput input_)
{
	// TODO: implement this.
}
}