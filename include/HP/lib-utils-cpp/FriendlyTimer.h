// (c) Copyright 2021 HP Development Company, L.P.

#pragma once
#include <chrono>

namespace HP {
namespace Utils {

    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;
    typedef std::chrono::time_point<std::chrono::steady_clock> tp;

    class FriendlyTimer
    {
    public:
        FriendlyTimer();
        ~FriendlyTimer();

        void start();
        void end();
        ms elapsed() const;
        ms runningElapsed() const;
        void printElapsed() const;

    private:
        tp t0;
        tp t1;
    };

}
}
