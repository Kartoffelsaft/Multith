#pragma once

#include <optional>
#include <chrono>
#include <memory>

#include "../actor.hpp"
#include "../printer/printer.hpp"
#include "../stateHandler/stateHandler.hpp"
#include "../staticAtomics.hpp"

auto  const TICK_TIME = std::chrono::milliseconds(15);
float const TICK_PER_SECOND = 1.f/std::chrono::duration_cast<std::chrono::seconds>(TICK_TIME).count();

class TickCoordinator
{
public:

    TickCoordinator() = default;
    ~TickCoordinator();

    void giveOutboundActors(
        std::weak_ptr<Actor<WindowHandler>> nprinter,
        std::weak_ptr<Actor<StateHandler>> nState
    );

    void tickLoop();

private:

    std::chrono::steady_clock::time_point lastTick;

    struct OutboundActors
    {
        void sendTicks();

        std::weak_ptr<Actor<WindowHandler>> printer;
        std::weak_ptr<Actor<StateHandler>> state;

    }; std::optional<OutboundActors> outboundActors;
};
