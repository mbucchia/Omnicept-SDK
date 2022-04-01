// (c) Copyright 2021 HP Development Company, L.P.

#include <string>
#pragma once

namespace HP {
namespace Utils {

    class SoftwareVersion
    {
    public:
        uint16_t major = 0;
        uint16_t minor = 0;
        uint16_t patch = 0;
        uint16_t build = 0;
        std::string toString() const;
    };
    std::ostream & operator<<(std::ostream & out, const SoftwareVersion &sv);

    class SoftwareInfoQuery
    {
        public:
        class GetVersionResult
        {
        public:
            bool success = false;
            std::string description;
            SoftwareVersion version;
            operator bool() const { return success; }
        };
            static GetVersionResult GetVersion(std::wstring filePath = L"");

    
    };

}
}
