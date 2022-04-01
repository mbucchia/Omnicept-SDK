// (c) Copyright 2021 HP Development Company, L.P.
#pragma once
#include <omnicept/lib-abi-cpp/MessageTypes.h>

namespace HP {
namespace Omnicept {
namespace Abi {
    
    class IDomainType {
    public: 
        virtual ~IDomainType() = default;
        virtual MessageType getMessageType() const = 0;
        
        template<typename DomainType, typename = std::enable_if_t<std::is_base_of_v<IDomainType, DomainType>>>
        bool isMessageA() const
        {
            return MessageTypeUtils::doesEnumMatchType<DomainType>(getMessageType());
        }

    };
}
}
}
