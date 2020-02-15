#include "./printer.hpp"

#include <cassert>

WindowHandler::WindowHandler() :
    window{
        sf::RenderWindow{
            sf::VideoMode(WINDOW_INIT_SIZE_X, WINDOW_INIT_SIZE_Y), 
            WINDOW_NAME
        }
    }
{}

WindowHandler::~WindowHandler()
{
    window.close();
}

void WindowHandler::onTick()
{
    handleInput();
}

void WindowHandler::giveOutboundActors(
    std::weak_ptr<Actor<StateHandler>> nstate,
    std::weak_ptr<Actor<PhysicsModel>> nmodel
){
    outboundActors = {
        nstate,
        nmodel
    };
}

void WindowHandler::renderPhysicsModel(PhysicsModelPrintable data)
{
    window.clear(sf::Color::Magenta);
    data.addToWindow(&window);
    
    window.display();
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
                {outboundActors->model.lock()->call(&PhysicsModel::pushPlayer, 0.0, -1.0);}
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {outboundActors->model.lock()->call(&PhysicsModel::pushPlayer, 0.0, 1.0);}
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {outboundActors->model.lock()->call(&PhysicsModel::pushPlayer, -1.0, 0.0);}
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {outboundActors->model.lock()->call(&PhysicsModel::pushPlayer, 1.0, 0.0);}
                break;
            default:
                break;
        }
    }
}
