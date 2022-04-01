// (c) Copyright 2021 HP Development Company, L.P.

#pragma once
#include <omnicept/lib-abi-cpp/GenericVersion.h>
#include <string>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Message version for domain types messages. */
    class MessageVersion : public HP::Omnicept::Abi::GenericVersion
    {
    public:
        MessageVersion(const std::string &version);
        virtual ~MessageVersion() = default;
        
        /*! @brief operator==.
        */
        bool operator==(const MessageVersion& other) const;
        bool operator<(const MessageVersion& other) const;
    };

    namespace MessageVersionConstants
    {
        const MessageVersion MessageVersion_1_0_0{ "1.0.0" }; //first message version for all versioned messages
        const MessageVersion MessageVersion_1_1_0{ "1.1.0" }; //second message version for versioned messages, currently only used for CognitiveLoad and CognitiveLoadInputFeature messages
    }

}

}
}
