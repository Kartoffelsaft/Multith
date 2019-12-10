#include "./printer.hpp"

Windowhandler::Windowhandler() : 
    window{
        sf::RenderWindow{
            sf::VideoMode(WINDOW_INIT_SIZE_X, WINDOW_INIT_SIZE_Y), 
            WINDOW_NAME
        }
    }
{
    
}

Windowhandler::~Windowhandler()
{
    window.close();
}

void Windowhandler::printTest()
{
    window.clear(sf::Color::Magenta);
    window.display();
}
