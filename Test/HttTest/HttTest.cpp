//Dmytro Konobrytskyi, 2014

#include "..\..\Code\HTT.h"
#include <iostream>

void RandSleep(int ms)
{
    std::this_thread::sleep_for(std::chrono::microseconds(1000 * ms + std::rand() % 700));
}

void Function3()
{
    HTT::TimingBlock tb("F3 block");
    RandSleep(1);
    TT.Tick("Sleep 1");
}

void Function2()
{
    HTT::TimingBlock tb("F2 block");
    RandSleep(5);
    TT.Tick("Sleep 5");
    Function3();
    RandSleep(2);
    TT.Tick("Sleep 2");
}

void Function1()
{
    HTT::TimingBlock tb("F1 block");
    RandSleep(3);
    TT.Tick("Sleep 3");
    Function2();
    RandSleep(7);
    TT.Tick("Sleep 7");
    Function3();
    RandSleep(10);
    TT.Tick("Sleep 10");
}

int main(int argc, char *argv[])
{
    TT.Tick("Start");
    RandSleep(11);
    TT.Tick("Sleep 11");
    Function1();
    TT.Tick("F1");
    RandSleep(12);
    TT.Tick("Sleep 12");

    for(auto &tick : TT.GetTicksList())
        std::cout << tick.first << " " << tick.second << std::endl;

    std::cout << TT.GetTicksListAsJson() << std::endl;

    return 0;
}