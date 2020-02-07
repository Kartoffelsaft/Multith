#include <chrono>
#include <thread>
#include <atomic>
#include <memory>

#include "./printer/printer.hpp"
#include "./tickCoordinator/tickCoordinator.hpp"
#include "./stateHandler/stateHandler.hpp"
#include "./actor.hpp"
#include "./staticAtomics.hpp"


int main()
{
    {
        std::shared_ptr<Actor<WindowHandler>> window{new Actor<WindowHandler>};
        std::shared_ptr<Actor<TickCoordinator>> tickCoordinator{new Actor<TickCoordinator>};
        std::shared_ptr<Actor<StateHandler>> state{new Actor<StateHandler>};

        tickCoordinator->call(&TickCoordinator::giveOutboundActors, 
            std::weak_ptr{window},
            std::weak_ptr{state}
        );
        window->call(&WindowHandler::giveOutboundActors, std::weak_ptr{state});
        tickCoordinator->call(&TickCoordinator::tickLoop);

        ActorReturn<bool> running;
        do
        {
            running = state->call(&StateHandler::isRunning);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
        while(running.get());
    }

    return 0;
}
