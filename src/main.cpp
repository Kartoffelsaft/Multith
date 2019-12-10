#include <cstdio>
#include <thread>
#include <chrono>

#include "./printer/printer.hpp"
#include "./actor.hpp"

int main()
{
    Actor<Windowhandler> a{new Windowhandler{}};

    a.call(&Windowhandler::printTest);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}
