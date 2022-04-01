// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <stdint.h>
#include <string>

namespace HP {
namespace Utils{
    class ClientUtil
    {
    public:
        static uint64_t getPid(const uint16_t port);
        static uint16_t getRemotePort(const uint16_t port);
        static std::wstring getPath(const uint16_t port);
        static std::string getHash(const uint16_t port);
        static std::string getHash(const std::wstring& path);
    };
}
}
