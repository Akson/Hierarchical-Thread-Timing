#pragma once
#include <string>
#include <thread>
#include <chrono>
#include <vector>

namespace HTT
{

////////////////////////////COMPATIBILITY HANDICAPS//////////////////////////////////////////////
//Maybe one day it will be implemented in a right way...
#define thread_local __declspec(thread)
#define USE_WINDOWS_QueryPerformanceCounter_TIMER

#ifdef USE_WINDOWS_QueryPerformanceCounter_TIMER
#include <windows.h>
struct WindowsHighResClock
{
    typedef long long                               rep;
    typedef std::nano                               period;
    typedef std::chrono::duration<rep, period>      duration;
    typedef std::chrono::time_point<WindowsHighResClock>   time_point;
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

class ThreadTimer
{
    //////////////////////////////////////////////////////////////////////////
    //THREAD LOCAL SINGLETON
public:
    static ThreadTimer *GetInstance()
    {
        thread_local static ThreadTimer *pInstance = nullptr;
        if(pInstance == nullptr)
            pInstance = new ThreadTimer;    //TODO: Fix this memory leak... somehow...
        return pInstance;
    }
private:
    ThreadTimer();
    ~ThreadTimer() {};
    ThreadTimer(ThreadTimer const &) {};
    void operator=(ThreadTimer const &) {};
    //THREAD LOCAL SINGLETON
    //////////////////////////////////////////////////////////////////////////

public:
    void StartBlock(const char *blockName);
    void EndBlock();
    void Tick(const char *eventName);
    void Flush(std::ostream &ss);
    void Restart();

private:
    SYSTEM_HIGH_RES_TIMER::time_point m_StartTime;
    std::vector<std::pair<double, std::string>> m_TicksList;
};

struct TimingBlock
{
    TimingBlock(const char *blockName) { HTT::ThreadTimer::GetInstance()->StartBlock(blockName); }
    ~TimingBlock(){ HTT::ThreadTimer::GetInstance()->EndBlock(); }
};

}