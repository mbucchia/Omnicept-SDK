// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <condition_variable>

namespace HP {
namespace Utils {

class Semaphore
{
public:
    Semaphore() : Semaphore(0)
    {
    }

    explicit Semaphore(size_t count) : m_count(count)
    {
    }

    virtual ~Semaphore() = default;

    void notify(size_t count = 1)
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_count += count;

        for (size_t i = 0; i < count; i++)
        {
            m_cv.notify_one();
        }
    }

    void wait()
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_cv.wait(lock, [&] { return m_count > 0; });

        --m_count;
    }

private:
    size_t m_count;
    std::mutex m_mutex;
    std::condition_variable m_cv;
};

}
}
