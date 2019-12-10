#pragma once

#include <SFML/Graphics.hpp>

static char const * const WINDOW_NAME{"Multith"};
static int  const         WINDOW_INIT_SIZE_X{800};
static int  const         WINDOW_INIT_SIZE_Y{600};

class Windowhandler
{
public:
    Windowhandler();
    ~Windowhandler();

    void printTest();

private:
    
    sf::RenderWindow window;
};
