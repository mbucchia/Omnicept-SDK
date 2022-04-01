// (c) Copyright 2019-2021 HP Development Company, L.P.

#pragma once
#include <stdint.h>
#include <ostream>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Specifies the timestamp collection */
    class Timestamp
    {
    public:
        Timestamp();
        virtual ~Timestamp() = default;
        
        int64_t systemTimeMicroSeconds; /*!< @brief Measured when an %Omnicept extension receives data from a device or generates a message */
        
        int64_t hardwareTimeMicroSeconds;/*!< @brief The time at which a sample was captured according to a sensor device's hardware clock, independent of system time */
        
        int64_t omniceptTimeMicroSeconds; /*!< @brief Synthetic timestamp used for sensor fusion based on hardware time and system time, provided on the system time timeline */

        bool operator== (const Timestamp& other) const;
        friend std::ostream& operator<< (std::ostream &out, const Timestamp&);
    };
}

}
}
