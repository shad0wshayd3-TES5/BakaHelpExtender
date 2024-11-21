#pragma once

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"

using namespace std::literals;

#ifdef SKYRIM_SUPPORT_AE
#	define OFFSET(se, ae) ae
#else
#	define OFFSET(se, ae) se
#endif
