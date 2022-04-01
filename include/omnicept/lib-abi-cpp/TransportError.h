// (c) Copyright 2018-2021 HP Development Company, L.P.

#pragma once
#include <stdexcept>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Used for problems in transport, meaning that the underlying transport
    * mechanism could not send or receive bytes.
    */
    class TransportError : public std::logic_error
    {
    public:
        explicit TransportError(const std::string& what_arg);
        explicit TransportError(const char* what_arg);
        virtual ~TransportError() = default;
    };
}
}
}