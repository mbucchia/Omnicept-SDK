// (c) Copyright 2021 HP Development Company, L.P.

#pragma once
#include <stdexcept>
#include <string>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Used for failures when attempting to send or receive on a connection that is not connected any more
    */
    class NotConnectedError : public std::runtime_error
    {

    public:
        explicit NotConnectedError(const std::string& what_arg);
        explicit NotConnectedError(const char* what_arg);
        virtual ~NotConnectedError() = default;
    };

}

}
}
