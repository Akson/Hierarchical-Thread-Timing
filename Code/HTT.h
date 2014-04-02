#pragma once
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include "HttCompatibility.h"

#define TT HTT::ThreadTimer::GetInstance()

namespace HTT
{

class ThreadTimer
{
    //////////////////////////////////////////////////////////////////////////
    //THREAD LOCAL SINGLETON
public:
    static ThreadTimer &GetInstance()
    {
        thread_local static ThreadTimer *pInstance = nullptr;
        if(pInstance == nullptr)
            pInstance = new ThreadTimer;    //TODO: Fix this memory leak... somehow...
        return *pInstance;
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
    std::vector<std::pair<double, std::string>> &GetTicksList();
    void Restart();

private:
    SYSTEM_HIGH_RES_TIMER::time_point m_StartTime;
    std::vector<std::pair<double, std::string>> m_TicksList;
};

struct TimingBlock
{
    TimingBlock(const char *blockName) { TT.StartBlock(blockName); }
    ~TimingBlock() { TT.EndBlock(); }
};

}