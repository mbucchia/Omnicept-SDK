// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#ifdef WIN32
#include <HP/lib-utils-cpp/win/WinClientUtil.h>
#else
#error IClientUtil is not defined for this platform.
#endif