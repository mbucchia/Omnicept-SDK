// (c) Copyright 2019-2021 HP Development Company, L.P.

#pragma once
#include <vector>
#include <omnicept/lib-abi-cpp/SensorInfo.h>
#include <omnicept/lib-abi-cpp/DomainData.h>
#include <omnicept/lib-abi-cpp/Timestamp.h>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Domain type for Cognitive Load prediction.*/
    class CognitiveLoad : public DomainData
    {
    public:
        CognitiveLoad();
        virtual ~CognitiveLoad() = default;

        float cognitiveLoad; /*!< @brief Continuous estimate of cognitive load in range [0.f, 1.f] where 0.f is lowest cognitive load, and 1.f is the highest cognitive load */
        float standardDeviation; /*!< @brief A prediction error considering cognitive load as the center of a normal distribution */
        //! @cond
        std::string dataState; /*!< \warning unused field */
        Timestamp startDataCollectTime; /*!< \warning unused field */
        Timestamp endDataCollectTime; /*!< \warning unused field */
        //! @endcond
        bool operator== (const CognitiveLoad& other) const;
        bool dataEquals(const DomainData& other) const override;
        
        std::string toString() const;
        MessageVersion getLatestMessageVersion() const override;
        MessageType getMessageType() const override;
    };

    std::ostream & operator<< (std::ostream &out, const CognitiveLoad&);
}
}
}
