#include <SFML/Window/ContextSettings.hpp>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>
#include <fstream>

#include "./printer/printer.hpp"
#include "./tickCoordinator/tickCoordinator.hpp"
#include "./stateHandler/stateHandler.hpp"
#include "./physicsModel/physicsModel.hpp"
#include "../multithlib/actor.hpp"
#include "../tomlplusplus/toml.hpp"
#include "./settings.hpp"
#include "./staticAtomics.hpp"


int main()
{
    Settings const config{toml::parse_file("./settings.toml")};

    std::shared_ptr<multith::Actor<WindowHandler>> window{new multith::Actor<WindowHandler>{&config}};
    std::shared_ptr<multith::Actor<TickCoordinator>> tickCoordinator{new multith::Actor<TickCoordinator>};
    std::shared_ptr<multith::Actor<StateHandler>> state{new multith::Actor<StateHandler>};
    std::shared_ptr<multith::Actor<PhysicsModel>> model{new multith::Actor<PhysicsModel>};

    auto a = tickCoordinator->callBlockable(&TickCoordinator::giveOutboundActors, 
        std::weak_ptr{window},
        std::weak_ptr{state}
    );
    auto b = window->callBlockable(&WindowHandler::giveOutboundActors, 
        std::weak_ptr{state},
        std::weak_ptr{model}
    );
    auto c = model->callBlockable(&PhysicsModel::giveOutboundActors,
        std::weak_ptr{window}
    );

    tickCoordinator->callBlockable(&TickCoordinator::tickLoop);

    multith::ActorReturn<bool> running;
    do
    {
        running = state->callUnblockable(&StateHandler::isRunning);
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    while(running.get());

    return 0;
}
