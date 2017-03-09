// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#ifndef _IMAGINECOMMONCOMMON_H
#define _IMAGINECOMMONCOMMON_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>
#include <cstring>
#include <string>
#include <limits>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <list>
#include <ctime>
#if !_WIN32
#include <sys/times.h>
#include <unistd.h>
#endif

#ifdef _WIN32
#undef RGB
#endif

/// \namespace Imagine
/// Imagine++ namespace.
/// Namespace for Imagine++ libraries
namespace Imagine {
}

/// \defgroup Common Common Library
/// @{
/// \example Common/test/test.cpp
/// @}

#include "Common/Base.h"       // Common
#include "Common/FArray.h"     // Fixed Arrays (static allocation)
#include "Common/FVector.h"    // Fixed vectors (static allocation)
#include "Common/FMatrix.h"    // Fixed matrices (static allocation)
#include "Common/Color.h"      // Colors
#include "Common/Array.h"      // Arrays (referenced counted)
#include "Common/Coords.h"     // nD coordinates (for MultiArrays)
#include "Common/MultiArray.h" // nD arrays (referenced counted)
#include "Common/Random.h"     // Random
#include "Common/Timer.h"      // Timer
#include "Common/IO.h"         // IO

# endif
