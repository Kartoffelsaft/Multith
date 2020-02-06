#pragma once

#include <SFML/Graphics.hpp>

#include <optional>

#include "../actor.hpp"
#include "../staticAtomics.hpp"
#include "../stateHandler/stateHandler.hpp"

static char const * const WINDOW_NAME{"Multith"};
static int  const         WINDOW_INIT_SIZE_X{800};
static int  const         WINDOW_INIT_SIZE_Y{600};

class WindowHandler
{
public:
    WindowHandler();
    ~WindowHandler();

    void onTick();

    void giveOutboundActors(
        std::weak_ptr<Actor<StateHandler>> nstate
    );

private:

    void render();
    void handleInput();

    sf::CircleShape testShape;
    int circleX;
    
    sf::RenderWindow window;

    struct OutboundActors{
        std::weak_ptr<Actor<StateHandler>> state;
    }; std::optional<OutboundActors> outboundActors;
};
