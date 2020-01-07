#include "./printer.hpp"

WindowHandler::WindowHandler() : 
    window{
        sf::RenderWindow{
            sf::VideoMode(WINDOW_INIT_SIZE_X, WINDOW_INIT_SIZE_Y), 
            WINDOW_NAME
        }
    },
    testShape{sf::CircleShape{}},
    circleX{10}
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

void WindowHandler::render()
{
    window.clear(sf::Color::Magenta);
    window.draw(testShape);

    window.display();
}

void WindowHandler::handleInput()
{
    sf::Event e;

    if(window.pollEvent(e))
    {
        switch(e.type)
        {
            case sf::Event::Closed:
                StaticAtomics::running.store(false);
                break;
        }
    }
}
