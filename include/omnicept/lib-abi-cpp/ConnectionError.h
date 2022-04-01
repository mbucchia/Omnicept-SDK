// (c) Copyright 2019-2021 HP Development Company, L.P.

#pragma once
#include <stdexcept>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Used for problems in connection, meaning that the underlying connection
    * mechanism failed.
    */
    class ConnectionError : public std::logic_error
    {
    public:
        explicit ConnectionError(const std::string& what_arg);
        explicit ConnectionError(const char* what_arg);
        virtual ~ConnectionError() = default;
    };
}
}
}