// (c) Copyright 2020-2021 HP Development Company, L.P.

#pragma once
#include <omnicept/lib-abi-cpp/SensorInfo.h>
#include <omnicept/lib-abi-cpp/DomainData.h>
#include <omnicept/lib-abi-cpp/DataFrame.h>
#include <omnicept/lib-abi-cpp/Timestamp.h>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Domain type for time facial camera shutter is open.
     *
     */
    class VSync : public DomainData
    {
    public:
        VSync();
        virtual ~VSync() override = default;

        bool operator == (const VSync& other) const;
        virtual bool dataEquals(const DomainData& other) const override;
        std::string toString() const;
        MessageType getMessageType() const override;
        MessageVersion getLatestMessageVersion() const override;
    };

    std::ostream & operator << (std::ostream &out, const VSync&);
}

}
}