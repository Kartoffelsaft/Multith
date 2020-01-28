#include <assert.h>

#include "./tickCoordinator.hpp"

void TickCoordinator::giveOutboundActors(
    Actor<WindowHandler> nprinter
){
    outboundActors = OutboundActors{
        nprinter
    };
}

TickCoordinator::~TickCoordinator()
{}

void TickCoordinator::tickLoop()
{
    assert(outboundActors.has_value());
    lastTick = std::chrono::steady_clock::now();
    while(StaticAtomics::running->load())
    {
        outboundActors->sendTicks();

        auto now = std::chrono::steady_clock::now();

        while(now < lastTick + TICK_TIME)
        {
            now = std::chrono::steady_clock::now();
            std::this_thread::sleep_for(lastTick + TICK_TIME - now);
        }

        lastTick += TICK_TIME;
    }
}

void TickCoordinator::OutboundActors::sendTicks()
{
    printer.call(&WindowHandler::onTick);
}
