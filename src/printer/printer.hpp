#pragma once

#include <SFML/Graphics.hpp>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <optional>

#include "../../multithlib/actor.hpp"
#include "../staticAtomics.hpp"
#include "../settings.hpp"
#include "../stateHandler/stateHandler.hpp"
#include "../physicsModel/physicsModel.hpp"
#include "../physicsModel/physicsModelPrintable.hpp"

static char const * const WINDOW_NAME{"Multith"};
static int  const         WINDOW_INIT_SIZE_X{800};
static int  const         WINDOW_INIT_SIZE_Y{600};

class PhysicsModel; // to fix some compiler recursion issue
class WindowHandler
{
public:
    WindowHandler(Settings const * const);
    ~WindowHandler();

    void renderPhysicsModel(PhysicsModelPrintable data);
    void onTick();

    void giveOutboundActors(
        std::weak_ptr<multith::Actor<StateHandler>> nstate,
        std::weak_ptr<multith::Actor<PhysicsModel>> nmodel
    );

private:

    void handleInput();
    sf::Texture postProcess(sf::Texture const unProcessed) const;

    Settings const * const settings;

    sf::RenderWindow window;
    unsigned long long frame;

    sf::Shader bgShader;

    sf::Shader ppFilmGrain;

    struct OutboundActors{
        std::weak_ptr<multith::Actor<StateHandler>> state;
        std::weak_ptr<multith::Actor<PhysicsModel>> model;
    }; std::optional<OutboundActors> outboundActors;
};
