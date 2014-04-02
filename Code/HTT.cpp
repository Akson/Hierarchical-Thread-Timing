#include "HTT.h"
#include <iostream>
#include <utility>
using namespace HTT;

HTT::ThreadTimer::ThreadTimer()
{
    Restart();
    sum = 0;
}

void HTT::ThreadTimer::Tick(const char *eventName)
{
    auto now = SYSTEM_HIGH_RES_TIMER::now();

    double curTimeMs = std::chrono::duration_cast<std::chrono::nanoseconds>(now - m_StartTime).count()*0.000001;
    sum += std::chrono::duration_cast<std::chrono::nanoseconds>(now - m_StartTime).count();
    //std::cout << "tick: " << std::chrono::duration_cast<std::chrono::nanoseconds>(now - m_StartTime).count()*0.000001 << " ms" << std::endl;
    m_TicksList.push_back(std::make_pair(curTimeMs, eventName));

    m_StartTime = now;
}

void HTT::ThreadTimer::Flush(std::ostream &ss)
{
    for(auto& tick : m_TicksList)
        ss << tick.first << " " << tick.second << std::endl;
}

void HTT::ThreadTimer::Restart()
{
    m_StartTime = SYSTEM_HIGH_RES_TIMER::now();
    m_TicksList.clear();
}
