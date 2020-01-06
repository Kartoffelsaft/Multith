#pragma once

#include <optional>
#include <chrono>

#include "../actor.hpp"
#include "../printer/printer.hpp"
#include "../staticAtomics.hpp"

auto  const TICK_TIME = std::chrono::milliseconds(15);
float const TICK_PER_SECOND = 1.f/std::chrono::duration_cast<std::chrono::seconds>(TICK_TIME).count();

class TickCoordinator
{
public:

    TickCoordinator() = default;
    ~TickCoordinator();

    void giveOutboundActors(
        Actor<WindowHandler> nprinter
    );

    void tickLoop();

private:

    std::chrono::steady_clock::time_point lastTick;

    struct OutboundActors
    {
        void sendTicks();

        Actor<WindowHandler> printer;
    }; std::optional<OutboundActors> outboundActors;
};
