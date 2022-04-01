// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include "HP/lib-utils-cpp/IDynamicLinker.h"
#include <memory>

namespace HP {
namespace Utils {

class DynamicLinkerFactory
{
public:
    DynamicLinkerFactory() = delete;
    
    static std::unique_ptr<IDynamicLinker> GetDynamicLinker();
};

}
}
