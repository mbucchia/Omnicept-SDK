// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#ifdef WIN32
#include <HP/lib-utils-cpp/win/WinCryptUtil.h>
#else
#error ICryptUtil is not defined for this platform.
#endif