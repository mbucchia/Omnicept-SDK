// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#ifdef WIN32
#include "HP/lib-utils-cpp/win/WinSoftwareInfoQuery.h"
#endif
#ifdef ANDROID
#include "HP/lib-utils-cpp/android/SoftwareInfoQuery.h"
#endif
