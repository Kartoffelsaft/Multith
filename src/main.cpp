#include <chrono>
#include <thread>
#include <atomic>

#include "./printer/printer.hpp"
#include "./tickCoordinator/tickCoordinator.hpp"
#include "./actor.hpp"
#include "./staticAtomics.hpp"


int main()
{
    Actor<WindowHandler> window{new WindowHandler{}};
    Actor<TickCoordinator> tickCoordinator{new TickCoordinator{}};

    tickCoordinator.call(&TickCoordinator::giveOutboundActors, window);
    tickCoordinator.call(&TickCoordinator::tickLoop);

    while(StaticAtomics::running.load())
    {std::this_thread::sleep_for(std::chrono::milliseconds(500));}

    return 0;
}
