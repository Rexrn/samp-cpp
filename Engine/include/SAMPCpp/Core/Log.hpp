#pragma once

#include SAMPCPP_PCH

#include <SAMPCpp/Core/TypesAndDefinitions.hpp>

namespace samp_cpp
{

class ILogOutput;

enum class LogMessage : Int32
{
	Info,
	Warning,
	Error,
	FatalError
};


class Log
{
public:
	Log(ILogOutput* logOutput_ = nullptr);

	void setOutput(ILogOutput *logOutput_);

	bool push(LogMessage messageType_, std::string message_);

	ILogOutput* getOutput() const;

private:
	ILogOutput *m_logOutput = nullptr;
};
}