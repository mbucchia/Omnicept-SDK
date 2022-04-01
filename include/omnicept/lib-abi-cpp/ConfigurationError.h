// (c) Copyright 2018-2021 HP Development Company, L.P.

#pragma once
#include <stdexcept>

namespace HP {
namespace Omnicept {
namespace Abi {

    enum class ConfigurationErrorCode_t :uint8_t {
        UNKNOWN_ERROR = 0,
        FILE_NOT_FOUND,
        FILE_PATH_OVERFLOW,
        FILE_ACCESS_DENIED,
        FILE_CLOSE_FAILED,
        FILE_CORRUPTED,
        ATTRIBUTE_NOT_FOUND,
        ATTRIBUTE_WRITE_FAILED,
        ATTRIBUTE_NAME_INVALID,
        ATTRIBUTE_DELETE_FAILED,
        ATTRIBUTE_VALUE_OVERFLOW,
        ATTRIBUTE_VALUE_CORRUPTED,
        ATTRIBUTE_READ_FAILED
    };

    /*! @brief Used for problems with accessing or 
     * performing operations on configuration files and values
    */
    class ConfigurationError : public std::logic_error
    {
    public:
        explicit ConfigurationError(const std::string& what_arg, 
            const ConfigurationErrorCode_t errorCode = ConfigurationErrorCode_t::UNKNOWN_ERROR);
        explicit ConfigurationError(const char* what_arg, 
            const ConfigurationErrorCode_t errorCode = ConfigurationErrorCode_t::UNKNOWN_ERROR);
        ConfigurationErrorCode_t m_errorCode;
        virtual ~ConfigurationError() = default;
    };
}

}
}