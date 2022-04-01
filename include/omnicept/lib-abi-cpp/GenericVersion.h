// (c) Copyright 2021 HP Development Company, L.P.

#pragma once
#include <string>
namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Generic version class for messages or DLLs.*/
    class GenericVersion
    {
    public:
    
        GenericVersion(const std::string &ver);
        
        virtual ~GenericVersion() = default;

        /*! @brief Gets the version in std::string.
        */
        virtual std::string toString() const;

        /*! @brief operator==
        */
        bool operator==(const GenericVersion &other) const;

        /*! @brief operator!=
        */
        bool operator!=(const GenericVersion& other) const;

    protected:
        std::string m_genericVersionString;
    };

}

}
}
