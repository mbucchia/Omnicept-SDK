// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <filesystem>

namespace HP {
namespace Utils {

    class FileSystem
    {
    public:
        static std::filesystem::path getExePath();
    };

}
}
