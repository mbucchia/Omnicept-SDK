// (c) Copyright 2019-2021 HP Development Company, L.P.

#pragma once
#include <vector>
#include <omnicept/lib-abi-cpp/SensorInfo.h>
#include <omnicept/lib-abi-cpp/DomainData.h>
#include <omnicept/lib-abi-cpp/Timestamp.h>

namespace HP {
namespace Omnicept {
namespace Abi {

    enum class CognitiveLoadTargetModel
    {
        UNKNOWN = 0,
        EYE_TRACKING = 1,
        EYE_TRACKING_PPG = 2
    };

    class NDimArrayFloat
    {
    public:
        NDimArrayFloat() = default;
        virtual ~NDimArrayFloat() = default;

        std::vector<uint32_t> shape;
        std::vector<float> valuesFlat;

        bool operator== (const NDimArrayFloat& other) const;

        std::string toString() const;
    };

    std::ostream& operator<< (std::ostream& out, const NDimArrayFloat&);

    /*! @brief Domain type for Cognitive Load Input Feature data.*/
    class CognitiveLoadInputFeature : public DomainData
    {
    public:
        CognitiveLoadInputFeature();
        virtual ~CognitiveLoadInputFeature() = default;

        std::string dataState;
        Timestamp startDataCollectTime;
        Timestamp endDataCollectTime;
        NDimArrayFloat features;
        CognitiveLoadTargetModel targetModel;

        bool operator== (const CognitiveLoadInputFeature& other) const;
        bool dataEquals(const DomainData& other) const override;

        std::string toString() const;
        MessageVersion getLatestMessageVersion() const override;
        MessageType getMessageType() const override;
    };

    std::ostream& operator<< (std::ostream &out, const CognitiveLoadInputFeature&);
}
}
}