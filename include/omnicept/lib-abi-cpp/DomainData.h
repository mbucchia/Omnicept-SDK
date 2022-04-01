// (c) Copyright 2019-2021 HP Development Company, L.P.

#pragma once

#include <omnicept/lib-abi-cpp/GenericMessage.h>
#include <omnicept/lib-abi-cpp/MessageTypes.h>
#include <omnicept/lib-abi-cpp/SensorInfo.h>
#include <omnicept/lib-abi-cpp/Timestamp.h>

#include <vector>
#include <string>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Base class for filterable timestamped domain type data */
    class DomainData : public GenericMessage
    {
    public:
        
        virtual ~DomainData() = default;

        SensorInfo sensorInfo;
        Timestamp timestamp;
        friend std::ostream& operator<< (std::ostream &out, const DomainData&);
        std::string toString() const;

        bool operator==(const DomainData& other) const;
        virtual bool dataEquals(const DomainData& other) const = 0;
    protected:
        DomainData() = default;
    };
}

}
}