// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include "HP/lib-utils-cpp/Semaphore.h"

#include <memory>
#include <atomic>
#include <mutex>
#include <string>
#include <thread>

namespace HP {
namespace Utils {

    /*! @brief A simple mix-in to provide a consistent interface for starting and stopping threaded objects.
    * Main purpose is to provide a consistent way to request threads to stop, otherwise just a very lean wrapper
    * around std::thread.
    */
    class ThreadOwner
    {
    public:
        virtual ~ThreadOwner();
        /*! @brief Start the thread inside this object. Idempotent.*/
        virtual void start();
        /*! @brief Ask that this thread stops when it is convenient, asynchronously. */
        virtual void requestStop();
        /*! @brief Joins the thread the thread whenever it completes, does not request a stop.
        * @returns False if the thread was not joinable. Indicates that either the thread is not running
        * or that it was detached. */
        virtual bool join();
        /*! @brief Checks if the Thread should continue or not*/
        virtual bool shouldContinue() const;
        /*! @brief Gets the thread id of this object's thread
        * @returns this object's thread id if the thread is not null, otherwise returns a thread id that doesn't identify a thread*/
        std::thread::id getThreadId() const;
    protected:
        /*! @brief Constructor is protected to prevent instantiation of this mix-in alone.*/
        ThreadOwner(std::string threadName);
        /*! @brief Inheritors overload threadFunction to provide their own function to be used.*/
        virtual void threadFunction() = 0;

        /*! @brief Do not call detatch on this thread. The whole point of this class is that it owns
        * this thread and can shut it down when desired. */
        std::shared_ptr<std::thread> m_thread;
        std::recursive_mutex m_mutex;
        std::string m_threadName;
        Semaphore m_threadShutdown;
    private:
        std::atomic<bool> m_shouldThreadContinue;
    };

}
}
