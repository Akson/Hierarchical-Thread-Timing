#pragma once
////////////////////////////COMPATIBILITY HANDICAPS//////////////////////////////////////////////
//Maybe one day it will be implemented in a right way...

//MSVS2013U1 does not recognize thread_local but has TLS
#if defined(_MSC_VER) && _MSC_VER <= 1800
#define thread_local __declspec(thread)
#else
//Lets hope that your compiler knows about it...
#endif

//MSVS2013U1 maps chrono::high_resolution_clock to low resolution (~1ms) timer, so we use QueryPerformanceCounter
#if defined(_MSC_VER) && _MSC_VER <= 1800
#include <windows.h>
struct WindowsHighResClock
{
    typedef long long rep;
    typedef std::nano period;
    typedef std::chrono::duration<rep, period> duration;
    typedef std::chrono::time_point<WindowsHighResClock> time_point;
    static const bool is_steady = true;

    static time_point now()
    {
        LARGE_INTEGER count;
        QueryPerformanceCounter(&count);
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        return time_point(duration(count.QuadPart * static_cast<rep>(period::den) / frequency.QuadPart));
    }
};
#define SYSTEM_HIGH_RES_TIMER WindowsHighResClock
#else
#define SYSTEM_HIGH_RES_TIMER std::chrono::high_resolution_clock
#endif
////////////////////////////COMPATIBILITY HANDICAPS//////////////////////////////////////////////
