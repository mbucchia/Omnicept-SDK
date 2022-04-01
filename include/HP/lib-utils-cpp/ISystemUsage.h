// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

namespace HP {
namespace Utils {

    class ISystemUsage
    {
    public:
        ISystemUsage() = default;
        virtual ~ISystemUsage() = default;

        /*! @brief Get % of local virtual memory used
         *
         * @return float local virtual memory used
         */
        virtual float getLocalVirtualMemoryUsage() = 0;

        /*! @brief Get % of global virtual memory used
         *
         * @return float global virtual memory used
         */
        virtual float getGlobalVirtualMemoryUsage() = 0;

        /*! @brief Get % of local physical memory used
         *
         * @return float local physical memory used
         */
        virtual float getLocalPhysicalMemoryUsage() = 0;

        /*! @brief Get % of global physical memory used
         *
         * @return float global physical memory used
         */
        virtual float getGlobalPhysicalMemoryUsage() = 0;

        /*! @brief Get local cpu load
         * returns the percent of the CPU that this process
         * has used since the last time the method was called.
         * If there is not enough information, -1 is returned.
         *
         * @return float local cpu load
         */
        virtual float getLocalCpuLoad() = 0;

        /*! @brief Get global cpu load
         * Returns 100.0f for "CPU fully pinned", 0.0f for "CPU idle"
         *
         * @return float global cpu load
        */
        virtual float getGlobalCpuLoad() = 0;
    };

}
}
