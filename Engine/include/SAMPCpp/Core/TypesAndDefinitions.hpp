#pragma once
#include SAMPCPP_PCH



#ifndef const_a
	#define const_a const auto
#endif

#ifndef volatile_a
	#define volatile_a volatile auto
#endif

#ifndef cv_a
	#define cv_a const volatile auto
#endif

// Include types:

// By default, include types also in global namespace:
#ifndef SAMP_EDGENGINE_ONLY_IN_NAMESPACE
	#define SAMP_EDGENGINE_SKIP_NAMESPACE
		#include "TypesAndDefinitions.inl"
	#undef SAMP_EDGENGINE_SKIP_NAMESPACE
#endif

#include "TypesAndDefinitions.inl"