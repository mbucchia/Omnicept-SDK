// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <omnicept/lib-abi-cpp/DomainData.h>
#include <omnicept/lib-abi-cpp/DataFrame.h>

namespace HP {
namespace Omnicept {
namespace Abi {

    class IMU3AxisValues
    {
    public:
        IMU3AxisValues();
        IMU3AxisValues(float x, float y, float z);
        virtual ~IMU3AxisValues() = default;

        float x;
        float y;
        float z;
        bool operator ==(const IMU3AxisValues& other) const;
        std::string toString() const;
    };

    std::ostream& operator<< (std::ostream& out, const IMU3AxisValues& imu3ax);
    //------------------------------------------------------------------------
    /*! @brief Domain type for inertial measurement unit (%IMU) data.
     *
     *  A single IMU contains six data sets, including x-y-z axis of accelerometer
     *  and x-y-z axis of gyroscope.
     */
    class IMU : public DomainData
    {
    public:
        IMU();
        IMU(IMU3AxisValues accValues, IMU3AxisValues gyroValues);
        virtual ~IMU() = default;

        /*! @brief Accelerometer IMU3AxisValues.
        *
        * +x is up, +y is left, +z is forward from user.
        * Units are G's (9.8 m/s^2)
        */
        IMU3AxisValues acc;

        /*! @brief Gyro IMU3AxisValues.
        *
        * x is yaw, y is pitch, z is roll. 
        * +x when the user turning their head to the right
        * +y when the user looks downwards
        * +z when the user tilts their head to the right
        * 
        * Units are degrees per second
        */
        IMU3AxisValues gyro;

        bool operator == (const IMU& other) const;
        bool dataEquals(const DomainData& other) const override;
        std::string toString() const;
        MessageType getMessageType() const override;
        MessageVersion getLatestMessageVersion() const override;
    };

    std::ostream& operator<< (std::ostream& out, const IMU&);
    //-------------------------------------------------------------------------
    /*! @brief Domain type for IMU Frames.
     *
     *  The Frame contains one or more IMU data and
     *  a timestamp that represents the latest data.
     */
    class IMUFrame : public DataFrame<IMU>
    {
    public:
        IMUFrame();
        virtual ~IMUFrame() = default;
        MessageType getMessageType() const override;
        MessageVersion getLatestMessageVersion() const override;
    };
}
}
}
