#include <assert.h>

#include "./tickCoordinator.hpp"

void TickCoordinator::giveOutboundActors(
    std::weak_ptr<multith::Actor<WindowHandler>> nprinter,
    std::weak_ptr<multith::Actor<StateHandler>> nstate
){
    outboundActors = OutboundActors{
        nprinter,
        nstate,
    };
}

TickCoordinator::~TickCoordinator()
{}

void TickCoordinator::tickLoop()
{
    assert(outboundActors.has_value());
    lastTick = std::chrono::steady_clock::now();
    multith::ActorReturn<bool> running;
    do
    {
        outboundActors->sendTicks();
        running = outboundActors->state.lock()->callBlockable(&StateHandler::isRunning);

        auto now = std::chrono::steady_clock::now();

        while(now < lastTick + TICK_TIME)
        {
            now = std::chrono::steady_clock::now();
            std::this_thread::sleep_for(lastTick + TICK_TIME - now);
        }

        lastTick += TICK_TIME;
    }
    while(running.get());
}

void TickCoordinator::OutboundActors::sendTicks()
{
    printer.lock()->callUnblockable(&WindowHandler::onTick);
}
