// (c) Copyright 2018-2021 HP Development Company, L.P.

#pragma once
#include <stdexcept>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Used for problems in protocol, meaning that the wrong kinds 
    * of messages are seen, or they are observed in the wrong order. 
    */
    class ProtocolError : public std::logic_error
    {
    public:
        explicit ProtocolError(const std::string& what_arg);
        explicit ProtocolError(const char* what_arg);
        virtual ~ProtocolError() = default;
    };
}
}
}