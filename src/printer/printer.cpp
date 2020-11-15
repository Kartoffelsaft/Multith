#include "./printer.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cassert>

WindowHandler::WindowHandler() :
    window{
        sf::RenderWindow{
            sf::VideoMode(WINDOW_INIT_SIZE_X, WINDOW_INIT_SIZE_Y), 
            WINDOW_NAME
        }
    },
    frame{0}
{
    bgShader.loadFromFile(
        "./shaders/background/bg.frag", 
        sf::Shader::Type::Fragment
    );
}

WindowHandler::~WindowHandler()
{
    window.close();
}

void WindowHandler::onTick()
{
    handleInput();
    
    // pass tick through here instead of tickcoordinator
    // to prevent deadlock
    outboundActors->model.lock()->call(&PhysicsModel::onTick);
}

void WindowHandler::giveOutboundActors(
    std::weak_ptr<multith::Actor<StateHandler>> nstate,
    std::weak_ptr<multith::Actor<PhysicsModel>> nmodel
){
    outboundActors = {
        nstate,
        nmodel
    };
}

void WindowHandler::renderPhysicsModel(PhysicsModelPrintable data)
{
    auto size = window.getSize();

    sf::RenderTexture bgTexture;
    bgTexture.create(size.x, size.y);
    bgTexture.clear(sf::Color::Black);
    bgTexture.display();

    sf::Sprite bgSprite(bgTexture.getTexture());
    window.draw(bgSprite, &bgShader);

    data.addToWindow(&window, frame);
    
    window.display();

    frame++;
}

[[deprecated]]
void WindowHandler::render()
{
    // no real use now
}

void WindowHandler::handleInput()
{
    assert(outboundActors.has_value());
    sf::Event e;

    if(window.pollEvent(e))
    {
        switch(e.type)
        {
            case sf::Event::Closed:
                outboundActors->state.lock()->call(&StateHandler::close);
                break;
            case sf::Event::KeyPressed:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {outboundActors->model.lock()->call(&PhysicsModel::pushPlayer, 0.0, -10.0);}
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {outboundActors->model.lock()->call(&PhysicsModel::pushPlayer, 0.0, 10.0);}
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {outboundActors->model.lock()->call(&PhysicsModel::pushPlayer, -10.0, 0.0);}
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {outboundActors->model.lock()->call(&PhysicsModel::pushPlayer, 10.0, 0.0);}
                break;
            default:
                break;
        }
    }
}
