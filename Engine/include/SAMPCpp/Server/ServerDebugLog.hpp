#pragma once

#include SAMPCPP_PCH

#include <SAMPCpp/Core/TextInc.hpp>
#include <SAMPCpp/Core/BasicInterfaces/LogOutput.hpp>
#include <SAMPCpp/Core/Log.hpp>

extern class samp_cpp::IGameMode* GameMode;

#ifdef DEBUG
	#define EDGE_LOG_DEBUG(messageType_, ...) \
		if (GameMode) \
			GameMode->debugLog.push( samp_cpp::LogMessage:: messageType_, samp_cpp::text::format( __VA_ARGS__ ) );
#else
	#define EDGE_LOG_DEBUG(...)
#endif