// (c) Copyright 2021 HP Development Company, L.P.

#pragma once
#include <HP/lib-utils-cpp/IUuid.h>
#include <memory>

namespace HP {
namespace Utils {

    struct UuidFactory
    {
        UuidFactory() = default;
        virtual ~UuidFactory() = default;

        static std::shared_ptr<IUuid> GenerateRandom();
        static std::shared_ptr<IUuid> ParseString(const std::string&);
    };

}
}