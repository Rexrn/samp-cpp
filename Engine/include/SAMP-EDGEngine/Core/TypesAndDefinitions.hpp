#pragma once

#ifndef const_a
#define const_a const auto
#endif

#ifndef volatile_a
#define volatile_a volatile auto
#endif

#ifndef cv_a
#define cv_a const volatile auto
#endif

namespace samp_edgengine
{
using Int8		= std::int8_t;
using Int16		= std::int16_t;
using Int32		= std::int32_t;
using Int64		= std::int64_t;
using Uint8		= std::uint8_t;
using Uint16	= std::uint16_t;
using Uint32	= std::uint32_t;
using Uint64	= std::uint64_t;
}
