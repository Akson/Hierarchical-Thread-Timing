//Dmytro Konobrytskyi, 2014

#include "..\..\Code\HTT.h"
#include <iostream>

void RandSleep(int ms)
{
    std::this_thread::sleep_for(std::chrono::microseconds(1000*ms + std::rand()%700));
}

void Function3()
{
    HTT::TimingBlock tb("F3 block");
    RandSleep(1);
    HTT::ThreadTimer::GetInstance()->Tick("Sleep 1");
}

void Function2()
{
    HTT::TimingBlock tb("F2 block");
    RandSleep(5);
    HTT::ThreadTimer::GetInstance()->Tick("Sleep 5");
    Function3();
    RandSleep(2);
    HTT::ThreadTimer::GetInstance()->Tick("Sleep 2");
}

void Function1()
{
    HTT::TimingBlock tb("F1 block");
    RandSleep(3);
    HTT::ThreadTimer::GetInstance()->Tick("Sleep 3");
    Function2();
    RandSleep(7);
    HTT::ThreadTimer::GetInstance()->Tick("Sleep 7");
    Function3();
    RandSleep(10);
    HTT::ThreadTimer::GetInstance()->Tick("Sleep 10");
}

int main(int argc, char* argv[])
{
    HTT::ThreadTimer::GetInstance()->Tick("Start");
    RandSleep(11);
    HTT::ThreadTimer::GetInstance()->Tick("Sleep 11");
    Function1();
    HTT::ThreadTimer::GetInstance()->Tick("F1");
    RandSleep(12);
    HTT::ThreadTimer::GetInstance()->Tick("Sleep 12");

    HTT::ThreadTimer::GetInstance()->Flush(std::cout);

    return 0;
}