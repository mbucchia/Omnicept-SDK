// (c) Copyright 2019-2021 HP Development Company, L.P.

#pragma once

#include <string>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Uniquely identifies a sensor. */
    class SensorDeviceId
    {
    public:
        SensorDeviceId() = default;
        SensorDeviceId(const SensorDeviceId&) = default;
        SensorDeviceId(SensorDeviceId&&) = default;
        SensorDeviceId& operator = (const SensorDeviceId&) = default;
        SensorDeviceId& operator = (SensorDeviceId&&) = default;

        SensorDeviceId(const std::string& id, const std::string& subId);

        virtual ~SensorDeviceId() = default;

        std::string id; /*!< @brief An identifier for a sensor, for example, a sensor type or model number. */
        std::string subId; /*!< @brief A further identifier, for example, to distinguish between multiple kinds of sensor hardware or multiple present sensors. */

        bool operator== (const SensorDeviceId& other) const;
        friend std::ostream& operator<< (std::ostream &out, const SensorDeviceId&);

        bool operator<(const SensorDeviceId& rhs) const;
    };

    /*! @brief Uniquely identifies a sensor and provides filterable or configurable information about it. */
    class SensorInfo
    {
    public:
        SensorInfo();
        SensorInfo(const SensorDeviceId& deviceId, const std::string& location);
        SensorInfo(const SensorInfo&) = default;
        SensorInfo(SensorInfo&&) = default;
        SensorInfo& operator = (const SensorInfo&) = default;
        SensorInfo& operator = (SensorInfo&&) = default;
        SensorInfo(const std::string& id, const std::string& subid, const std::string& location);

        virtual ~SensorInfo() = default;

        SensorDeviceId deviceId; /*!< @brief the sensor's unique identifier */
        std::string location; /*!< @brief The sensor's physical location, such as the body part where contact is made and measurements are taken. */

        bool operator== (const SensorInfo& other) const;
        friend std::ostream& operator<< (std::ostream &out, const SensorInfo&);

        bool operator<(const SensorInfo& rhs) const;
    };
}

}
}