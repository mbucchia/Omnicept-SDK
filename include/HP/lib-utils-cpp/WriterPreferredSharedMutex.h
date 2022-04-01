// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <shared_mutex>

namespace HP {
namespace Utils {

    class WriterPreferredSharedMutex
    {
    public:
        WriterPreferredSharedMutex() = default;
        ~WriterPreferredSharedMutex() = default;
        WriterPreferredSharedMutex(WriterPreferredSharedMutex&&) = delete;
        WriterPreferredSharedMutex(const WriterPreferredSharedMutex&) = delete;
        WriterPreferredSharedMutex& operator = (WriterPreferredSharedMutex&&) = delete;
        WriterPreferredSharedMutex& operator = (const WriterPreferredSharedMutex&) = delete;

        void lock();
        void unlock();
        bool try_lock();
        void lock_shared();
        void unlock_shared();
        bool try_lock_shared();
    private:
        std::shared_mutex read, resource;
    };

}
}
