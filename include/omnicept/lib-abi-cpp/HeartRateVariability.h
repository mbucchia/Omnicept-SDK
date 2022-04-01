// (c) Copyright 2020-2021 HP Development Company, L.P.

#pragma once

#include <omnicept/lib-abi-cpp/DomainData.h>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Domain type for heart rate variability data.*/
    class HeartRateVariability : public DomainData
    {
    public:
        HeartRateVariability();

        virtual ~HeartRateVariability();
        float sdnn; /*!< @brief Standard deviation between two normal heart beats in milliseconds. Zero value indicates sensor signal quality is too poor to calculate. */
        float rmssd; /*!< @brief Root-mean square of successive differences in milliseconds. Zero value indicates sensor signal quality is too poor to calculate. */

        bool operator == (const HeartRateVariability& other) const;
        bool dataEquals(const DomainData& other) const override;
        std::string toString() const;
        MessageVersion getLatestMessageVersion() const override;
        MessageType getMessageType() const override;
    };

    std::ostream& operator<< (std::ostream &out, const HeartRateVariability&);
}

}
}
