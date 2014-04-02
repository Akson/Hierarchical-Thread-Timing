//Dmytro Konobrytskyi, 2014

#include "..\..\Code\HTT.h"
#include <iostream>

int main(int argc, char* argv[])
{
    for(int i = 0; i < 10000; i++)
    {
        HTT::ThreadTimer::GetInstance()->Tick("tick");
    }

    std::cout << std::endl << "AVG: " << HTT::ThreadTimer::GetInstance()->sum*0.000001 / 10000 << " ms" << std::endl;

    HTT::ThreadTimer::GetInstance()->Flush(std::cout);

    return 0;
}