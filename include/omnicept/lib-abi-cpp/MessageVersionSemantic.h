// (c) Copyright 2021 HP Development Company, L.P.

#pragma once
#include <omnicept/lib-abi-cpp/MessageVersion.h>
#include <string>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Message version semantic class for storing version specification logics.*/
    class MessageVersionSemantic
    {
    public:
    
        explicit MessageVersionSemantic(const std::string& semantic);
        MessageVersionSemantic(const MessageVersion& semantic);
        
        virtual ~MessageVersionSemantic() = default;

        /*! @brief Gets the version in std::string.
        */
        virtual std::string toString() const;

        /*! @brief Check a MessageVersion matches the semantic logic.
*/
        bool satisfy(const HP::Omnicept::Abi::MessageVersion &messageVer) const;

        bool operator<(const MessageVersionSemantic& rhs) const;

    protected:
        std::string m_versionSemanticString;

    };

    namespace MessageVersionSemanticConstants
    {
        const MessageVersionSemantic MessageVersionSemantic_WildCard{ "" };
    }
}

}
}