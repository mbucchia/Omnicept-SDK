// (c) Copyright 2019-2021 HP Development Company, L.P.

#pragma once
#include <vector>
#include <omnicept/lib-abi-cpp/SensorInfo.h>
#include <omnicept/lib-abi-cpp/DomainData.h>
#include <omnicept/lib-abi-cpp/DataFrame.h>

#include <iostream>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Domain type for byte message data.*/
    class ByteMessage : public GenericMessage
    {
    public:
        ByteMessage();
        ByteMessage(std::string id, std::string msg);

        virtual ~ByteMessage() = default;
        std::string id; /*!< @brief Identifier for the type of message */
        std::string message; /*!< @brief Body of the message as a string of bytes */ 

        bool operator == (const ByteMessage& other) const;
        MessageType getMessageType() const override;
        MessageVersion getLatestMessageVersion() const override;
    };

    std::ostream & operator << (std::ostream &out, const ByteMessage&);
}

}
}