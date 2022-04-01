// (c) Copyright 2020-2021 HP Development Company, L.P.

#pragma once

#include <exception>
#include <string>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Used for failures during the the handshake that attempts to create a connection
    * between a client and the %HP %Omnicept %Runtime.
    */
    class HandshakeError : public std::exception
    {

    public:
        explicit HandshakeError(const std::string& what_arg);
        explicit HandshakeError(const char* what_arg);
        const char* what() const noexcept override;
        virtual ~HandshakeError() = default;
    protected:
        std::string message;
    };

}

}
}
