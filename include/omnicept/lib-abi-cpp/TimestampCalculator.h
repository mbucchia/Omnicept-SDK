// (c) Copyright 2021 HP Development Company, L.P.

#pragma once
#include <stdint.h>
#include <ostream>
#include <functional>
#include <deque>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Utility class to handle calculation of interpolated HW timestamps and Omnicept Timestamp */
    class TimestampCalculator
    {
    public:
        struct PacketTimeInfo
        {
            int64_t hwTime;
            int64_t sysTime;
            uint8_t numSamples;

            int64_t sysDiff;
            int64_t hwDiff;
            double instantSkew;

            PacketTimeInfo(int64_t hw, int64_t sys, uint8_t num, int64_t sysD=0.0, int64_t hwD = 0, double iSkew = 1.0) :
                hwTime{ hw }, sysTime{ sys }, numSamples{ num }, sysDiff{ sysD }, hwDiff{ hwD }, instantSkew{ iSkew }{}
        };

        struct NextTimestampResult
        {
            int64_t hwInterpolatedTime = 0;
            int64_t omniceptTime = 0;
        };

        TimestampCalculator(double expectedSensorFrequency, size_t maxQueueSize = 50);
        virtual ~TimestampCalculator() = default;

        void addPacketTimeInfo(PacketTimeInfo timeInfo);
        NextTimestampResult getNextTimestamp();

        void notifyDeviceReset();

        /*! @brief Creates and returns a function to generates a sequence of linearly spaced values.
        *
        * @param start Starting value in range
        * @param end Ending value in range
        * @param num Number of values to produce
        * @param offset Produce only the final 'num' values in the linspace range (start, stop, num + offset).
        */
        static std::function<int64_t()> genLinspace(int64_t start, int64_t stop, uint8_t num, uint8_t offset=0);
        double calculateSkew();

        std::deque<PacketTimeInfo> packetTimeInfoQueue;

    private:
        void resetFrameInterpolate();
        std::function<int64_t()> m_interpolateNextHWTime;

        template<typename T>
        static T lerp(T v0, T v1, double t)
        {
            return static_cast<T>((1 - t) * v0 + t * v1);
        }

        double m_sensorFrequency;

        int64_t m_systemStartTime;
        int64_t m_lastSystemStartTime;
        int64_t m_correctedStartTime;


        int64_t m_hwStartTime;
        int64_t m_receivedSamples;
        size_t m_maxPacketTimeInfoQueueSize;

        double m_skewPrevious;
    };

}

}
}