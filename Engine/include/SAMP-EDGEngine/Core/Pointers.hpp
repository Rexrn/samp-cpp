#pragma once

#include SAMP_EDGENGINE_PCH

// Include pointers:

// By default, include pointers also in global namespace:
#ifndef SAMP_EDGENGINE_ONLY_IN_NAMESPACE
	#define SAMP_EDGENGINE_SKIP_NAMESPACE
		#include "Pointers.inl"
	#undef SAMP_EDGENGINE_SKIP_NAMESPACE
#endif

#include "Pointers.inl"