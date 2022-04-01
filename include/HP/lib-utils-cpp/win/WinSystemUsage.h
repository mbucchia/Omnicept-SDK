// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include "HP/lib-utils-cpp/ISystemUsage.h"
#include <mutex>
#include <Windows.h>
#include <psapi.h>

namespace HP {
namespace Utils {

    class SystemUsage : public ISystemUsage
    {
    public:
        SystemUsage();
        virtual ~SystemUsage() = default;

        /*! @brief Get % of local virtual memory used
         *
         * @return float local virtual memory used
         */
        virtual float getLocalVirtualMemoryUsage() override;

        /*! @brief Get % of global virtual memory used
         *
         * @return float global virtual memory used
         */
        virtual float getGlobalVirtualMemoryUsage() override;

        /*! @brief Get % of local physical memory used
         *
         * @return float local physical memory used
         */
        virtual float getLocalPhysicalMemoryUsage() override;

        /*! @brief Get % of global physical memory used
         *
         * @return float global physical memory used
         */
        virtual float getGlobalPhysicalMemoryUsage() override;

        /*! @brief Get % of local cpu load
         * returns the percent of the CPU that this process
         * has used since the last time the method was called.
         * If there is not enough information, -1 is returned.
         * If the method is recalled to quickly, the previous value
         * is returned.
         *
         * @return float local cpu load
         */
        virtual float getLocalCpuLoad() override;

        /*! @brief Get % of global cpu load
         * Returns 100.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in between
         * You'll need to call this at regular intervals, since it measures the load between
         * the previous call and the current one.  Returns -1.0 on error.
         *
         * @return float global cpu load
        */
        virtual float getGlobalCpuLoad() override;

    private:

        void getProcessMemoryInfo(MEMORYSTATUSEX& memInfo, PROCESS_MEMORY_COUNTERS_EX& pmc) const;
        uint64_t subtractTimes(const FILETIME& ftA, const FILETIME& ftB) const;

        bool hasEnoughTimePassed() const;
        bool isFirstLocalCpuCalc() const { return (m_timeOfLastLocalCpuCalc == 0); }

        FILETIME m_prevSystemKernelTime;
        FILETIME m_prevSystemUserTime;
        FILETIME m_prevProcKernelTime;
        FILETIME m_prevProcUserTime;
        float m_localCpuUsage;
        uint64_t m_timeOfLastLocalCpuCalc;
        std::mutex m_mtx;
    
        uint64_t fileTimeToInt64(const FILETIME & ft) const;
        float calculateGlobalCpuLoad(uint64_t idleTicks, uint64_t totalTicks);
        uint64_t m_previousTotalTicks;
        uint64_t m_previousIdleTicks;
    };

}
}
