// (c) Copyright 2018-2021 HP Development Company, L.P.

#pragma once
#include <omnicept/lib-abi-cpp/SensorInfo.h>
#include <omnicept/lib-abi-cpp/MessageTypes.h>
#include <omnicept/lib-abi-cpp/ConnectionIdentifier.h>
#include <omnicept/lib-abi-cpp/PackageDeclaration.h>
#include <HP/lib-utils-cpp/DataView.h>

#include <memory>
#include <stdint.h>
#include <string>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief ABC for all messages, the intermediate step between domain types and serialized bytes.*/
    class IMessage
    {
    public:
        virtual ~IMessage() = default;

        MessageType getMessageType() const { return getHeader().getType(); }

        virtual const PackageDeclaration& getHeader() const = 0;

        virtual const HP::Utils::DataView<uint8_t> getMessageByteView() const = 0;

        virtual const HP::Utils::DataView<uint8_t> getHeaderByteView() const = 0;

        virtual const HP::Utils::DataView<uint8_t> getBodyByteView() const = 0;

        /*! @brief Checks if an IMessage is a serialized DomainType message
        *
        * Use instead of hardcoding a MessageType into a check
        *
        * @tparam DomainType an Omnicept Message Type
        * @returns true if \p msg can be serialized to a DomainType, else false
        */
        template <class DomainType> bool isMessageA() const
        {
            return MessageTypeUtils::doesEnumMatchType<DomainType>(getMessageType());
        };

        /*! @brief Gets stringified type of serialized message if a valid name exists. 
        *
        * @returns stringified name for MessageType
        */
        std::string getMessageTypeString() const
        {
            std::string strType;
            MessageType type = getMessageType();
            if (MessageTypeStrings.find(type) != MessageTypeStrings.end())
            {
                strType = MessageTypeStrings.at(type);
            }
            else
            {
                strType = "unknownType_" + std::to_string(type);
            }
            return strType;
        }

    protected:
        IMessage() = default;
    };

}

}
}
