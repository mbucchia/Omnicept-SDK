// (c) Copyright 2018-2021 HP Development Company, L.P.

#pragma once
#include <stdexcept>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Used for problems in serialization, meaning that a domain type
    * could not be serialized/deserialized or that a nullptr was given.
    */
    class SerializationError : public std::logic_error
    {
    public:
        explicit SerializationError(const std::string& what_arg);
        explicit SerializationError(const char* what_arg);
        virtual ~SerializationError() = default;
    };
}
}
}