#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/Server/Command.hpp>
#include <SAMP-EDGEngine/Server/Server.hpp>

#include <istream>

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
	return std::find_if(_possibleInputs.begin(), _possibleInputs.end(),
		[&input_](std::string const &e_)
		{
			return input_ == e_;
		}) != _possibleInputs.end();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProcedureCommand::invoke(CommandInput input_)
{
	_function(input_);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TeleportCommand::invoke(CommandInput input_)
{
	// TODO: implement this.
}
}