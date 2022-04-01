// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#ifdef OMNICEPT_EXPERIMENTAL
#pragma message("warning: ****Experimental features enabled. Only use if you've been told****")
#include <omnicept/lib-abi-cpp/FacialEMG.h>
#include <omnicept/lib-abi-cpp/Expression.h>
#include <omnicept/lib-abi-cpp/SceneColor.h>
#else
#error ****In order to use experimental headers please set USE_OMNICEPT_EXPERIMENTAL to ON****
#endif
