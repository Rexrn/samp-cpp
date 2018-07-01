// This includes SAMPGDK library (the C++-way). 
#pragma once

#define SAMPGDK_AMALGAMATION
#define SAMPGDK_CPP_WRAPPERS

#if !defined(SAMPGDK_AMALGAMATION) || defined(ADVANCEDGDK_ACTIVE_PROJECT)
#include <sampgdk/sampgdk.h>
#else
#include "../../../Dependencies/sampgdk/sampgdk.h"
#endif
