#pragma once

#include <QuickMaffs/Everything.hpp>

#ifndef QUICKMAFFS_HEADER_ONLY
#error "QuickMaffs needs to be compiled separately! When QuickMaffs is properly linked, remove this error."
#endif

namespace samp_edgengine::math
{
// Unwrap quickmaffs namespace to agdk::math.
using namespace quickmaffs; 
}
