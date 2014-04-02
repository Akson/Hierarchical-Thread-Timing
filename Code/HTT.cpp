#include "HTT.h"
#include <iostream>
#include <utility>
using namespace HTT;

HTT::ThreadTimer::ThreadTimer()
{
    Restart();
}

void HTT::ThreadTimer::Restart()
{
    m_StartTime = SYSTEM_HIGH_RES_TIMER::now();
    m_TicksList.clear();
}

void HTT::ThreadTimer::Tick(const char *eventName)
{
    auto now = SYSTEM_HIGH_RES_TIMER::now();
    double curTimeMs = std::chrono::duration_cast<std::chrono::nanoseconds>(now - m_StartTime).count()*0.000001;
    m_TicksList.push_back(std::make_pair(curTimeMs, eventName));
}

void HTT::ThreadTimer::StartBlock(const char *blockName)
{
    std::string eventName = "_BLOCK_START_";
    eventName += blockName;
    Tick(eventName.c_str());
}

void HTT::ThreadTimer::EndBlock()
{
    Tick("_BLOCK_END_");
}

void HTT::ThreadTimer::Flush(std::ostream &ss)
{
    for(auto& tick : m_TicksList)
        ss << tick.first << " " << tick.second << std::endl;
}
