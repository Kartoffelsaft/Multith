#include <chrono>
#include <thread>
#include <atomic>
#include <memory>

#include "./printer/printer.hpp"
#include "./tickCoordinator/tickCoordinator.hpp"
#include "./stateHandler/stateHandler.hpp"
#include "./physicsModel/physicsModel.hpp"
#include "../multithlib/actor.hpp"
#include "./staticAtomics.hpp"


int main()
{
    {
        std::shared_ptr<multith::Actor<WindowHandler>> window{new multith::Actor<WindowHandler>};
        std::shared_ptr<multith::Actor<TickCoordinator>> tickCoordinator{new multith::Actor<TickCoordinator>};
        std::shared_ptr<multith::Actor<StateHandler>> state{new multith::Actor<StateHandler>};
        std::shared_ptr<multith::Actor<PhysicsModel>> model{new multith::Actor<PhysicsModel>};

        tickCoordinator->call(&TickCoordinator::giveOutboundActors, 
            std::weak_ptr{window},
            std::weak_ptr{state}
        );
        window->call(&WindowHandler::giveOutboundActors, 
            std::weak_ptr{state},
            std::weak_ptr{model}
        );
        model->call(&PhysicsModel::giveOutboundActors,
            std::weak_ptr{window}
        );
        tickCoordinator->call(&TickCoordinator::tickLoop);

        multith::ActorReturn<bool> running;
        do
        {
            running = state->call(&StateHandler::isRunning);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
        while(running.get());
    }

    return 0;
}
