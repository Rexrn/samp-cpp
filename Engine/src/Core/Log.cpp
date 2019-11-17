#include SAMPCPP_PCH

#include <SAMPCpp/Core/Log.hpp>

#include <SAMPCpp/Core/BasicInterfaces/LogOutput.hpp>

namespace samp_cpp
{

///////////////////////////////////////////////////
Log::Log(ILogOutput* logOutput_)
	: m_logOutput(logOutput_)
{
	
}

///////////////////////////////////////////////////
void Log::setOutput(ILogOutput *logOutput_)
{
	m_logOutput = logOutput_;
}

///////////////////////////////////////////////////
bool Log::push(LogMessage messageType_, std::string message_)
{
	if (m_logOutput)
	{
		m_logOutput->push(messageType_, std::move(message_));
		return true;
	}
	return false;
}


///////////////////////////////////////////////////
ILogOutput* Log::getOutput() const
{
	return m_logOutput;
}

}