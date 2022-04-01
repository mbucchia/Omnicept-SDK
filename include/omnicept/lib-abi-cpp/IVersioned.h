// (c) Copyright 2020 HP Development Company, L.P.
#pragma once
#include <omnicept/lib-abi-cpp/MessageVersion.h>

namespace HP {
namespace Omnicept {
namespace Abi {
    
    class IVersioned 
    {
    public: 
        virtual ~IVersioned() = default;
        virtual MessageVersion getMessageVersion() const
        {
            return m_version;
        }
        virtual void setMessageVersion(const MessageVersion& version)
        {
            m_version = version;
        }
        virtual MessageVersion getLatestMessageVersion() const = 0;
    protected:
        IVersioned(const MessageVersion& version = MessageVersionConstants::MessageVersion_1_0_0)
            : m_version{version}
        {
        }
        MessageVersion m_version;
    };
}
}
}
