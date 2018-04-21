// This includes SAMPGDK library (the C++-way). 
#pragma once

#define SAMPGDK_AMALGAMATION
#define SAMPGDK_CPP_WRAPPERS

#ifdef ADVANCEDGDK_ACTIVE_PROJECT
	#include <sampgdk/sampgdk.h>
#else
	// Note: if you changed location of this file, you must update the following path:
	#include "../../dependencies/sampgdk/sampgdk.h"
#endif
