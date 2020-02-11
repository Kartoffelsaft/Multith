#include "./printer.hpp"

#include <cassert>

WindowHandler::WindowHandler() :
    testShape{sf::CircleShape{}},
    circleX{10}, 
    window{
        sf::RenderWindow{
            sf::VideoMode(WINDOW_INIT_SIZE_X, WINDOW_INIT_SIZE_Y), 
            WINDOW_NAME
        }
    }
{
    testShape.setRadius(10);
    testShape.setFillColor(sf::Color::Green);
}

WindowHandler::~WindowHandler()
{
    window.close();
}

void WindowHandler::onTick()
{
    handleInput();
    circleX++;
    testShape.setPosition(circleX, 10);
    render();
}

void WindowHandler::giveOutboundActors(
        std::weak_ptr<Actor<StateHandler>> nstate
){
    outboundActors = {
        nstate
    };
}

void WindowHandler::render()
{
    window.clear(sf::Color::Magenta);
    window.draw(testShape);

    window.display();
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
            default:
                break;
        }
    }
}
