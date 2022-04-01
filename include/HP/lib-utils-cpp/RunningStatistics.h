// (c) Copyright 2021 HP Development Company, L.P.

#pragma once
#include <limits>
#include <cmath>
#include <cstdint>

namespace HP {
namespace Utils {

    /*! @vbrief Keeps statistics of running values */
    template <typename T>
    class RunningStatistics
    {
    public:
        RunningStatistics() = default;
        virtual ~RunningStatistics() = default;

        /*! @brief Updates the running statistics with a new value
         *
         * @param T new value
         */
        void update(const T value);

        /*! @brief Set the ddof for variance calculations
         *
         * The calculation of variance has a numerator with N - ddof.
         * For population variance, set ddof to 0. For sample variance,
         * set ddof to 1.
         *
         * @param uint16_t ddof the delta degrees of freedom
         */
        void setDDOF(uint16_t ddof)
        {
            m_ddof = ddof;
        }

        /*! @brief Get the number of values added*/
        uint64_t getCount() const;

        double getMean() const;

        T getMin() const;

        T getMax() const;

        double getVariance() const;

        double getStandardDeviation() const;

        void reset();

    protected:

        template <typename Y = T, typename std::enable_if<std::numeric_limits<Y>::has_infinity && std::numeric_limits<Y>::is_iec559, int>::type = 0 >
        Y getLowestRepresentionOfT() const { return -std::numeric_limits<Y>::infinity(); }

        template <typename Y = T, typename std::enable_if<!(std::numeric_limits<Y>::has_infinity && std::numeric_limits<Y>::is_iec559), int>::type = 0 >
        Y getLowestRepresentionOfT() const { return std::numeric_limits<Y>::lowest(); }

        template <typename Y = T, typename std::enable_if<std::numeric_limits<Y>::has_infinity, int>::type = 0 >
        Y getHighestRepresentionOfT() const { return std::numeric_limits<Y>::infinity(); }

        template <typename Y = T, typename std::enable_if<!std::numeric_limits<Y>::has_infinity, int>::type = 0 >
        Y getHighestRepresentionOfT() const { return std::numeric_limits<Y>::max(); }

        double m_mean{ 0 };
        T m_max{ getLowestRepresentionOfT() };
        T m_min{ getHighestRepresentionOfT() };
        double m_variance{ 0 };
        uint64_t m_count{ 0 };
        uint64_t m_ddof{ 0 };
    };

    template <typename T>
    void RunningStatistics<T>::update(const T newValue)
    {
        ++m_count;
        const auto oldMean = m_mean;
        m_mean = oldMean + (newValue - oldMean) / static_cast<double>(m_count);
        m_variance = m_variance + (newValue - oldMean)*(newValue - m_mean);
        if (newValue > m_max)
        {
            m_max = newValue;
        }
        if (newValue < m_min)
        {
            m_min = newValue;
        }
    };

    template <typename T>
    uint64_t RunningStatistics<T>::getCount() const
    {
        return m_count;
    };

    template <typename T>
    double RunningStatistics<T>::getMean() const
    {
        return m_mean;
    };

    template <typename T>
    T RunningStatistics<T>::getMin() const
    {
        return m_min;
    };

    template <typename T>
    T RunningStatistics<T>::getMax() const
    {
        return m_max;
    };

    template <typename T>
    double RunningStatistics<T>::getVariance() const
    {
        return (m_count > 1) ? m_variance / static_cast<double>(m_count - m_ddof) : 0;
    };

    template <typename T>
    double RunningStatistics<T>::getStandardDeviation() const
    {
        return std::sqrt(getVariance());
    };

    template <typename T>
    void RunningStatistics<T>::reset()
    {
        m_mean = 0;
        m_max = getLowestRepresentionOfT();
        m_min = getHighestRepresentionOfT();
        m_variance = 0;
        m_count = 0;
    };

}
}
