#pragma once

#include SAMPEDGENGINE_PCH

#ifdef DEBUG
	#define EDGE_LOG_DEBUG(messageType_, format_, ...) \
		if (GameMode) \
			GameMode->debugLog.push(samp_edgengine::LogMessage:: messageType_, samp_edgengine::text::ascii::format(format_, __VA_ARGS__));
#else
	#define EDGE_LOG_DEBUG(...)
#endif