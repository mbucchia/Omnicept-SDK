// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <string>
#include <HP/lib-utils-cpp/IUuid.h>

namespace HP {
namespace Utils {

    class UuidValidator
    {
    public:
        UuidValidator() = delete;
        static bool validateUuid(std::string toValidate);
        static bool validateUuid(const IUuid& toValidate);
    private:
        /* Regex for Uuid format: https://en.wikipedia.org/wiki/Universally_unique_identifier#Format
        */
        static constexpr const char * uuidRegex = "[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}";
    };

}
}
