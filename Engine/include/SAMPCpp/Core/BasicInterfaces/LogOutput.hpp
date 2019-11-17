#pragma once

#include SAMPCPP_PCH

#include <SAMPCpp/Core/TypesAndDefinitions.hpp>

namespace samp_cpp
{

enum class LogMessage : Int32;

class ILogOutput
{
public:
	virtual void push(LogMessage messageType_, std::string message_) = 0;
};

}