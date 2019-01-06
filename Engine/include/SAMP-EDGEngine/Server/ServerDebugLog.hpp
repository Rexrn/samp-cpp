#pragma once

#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/Core/TextInc.hpp>
#include <SAMP-EDGEngine/Core/BasicInterfaces/LogOutput.hpp>
#include <SAMP-EDGEngine/Core/Log.hpp>

extern class samp_edgengine::IGameMode* GameMode;

#ifdef DEBUG
	#define EDGE_LOG_DEBUG(messageType_, ...) \
		if (GameMode) \
			GameMode->debugLog.push( samp_edgengine::LogMessage:: messageType_, samp_edgengine::text::ascii::format( __VA_ARGS__ ) );
#else
	#define EDGE_LOG_DEBUG(...)
#endif