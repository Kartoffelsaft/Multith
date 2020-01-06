#pragma once

#include <SFML/Graphics.hpp>

#include "../staticAtomics.hpp"

static char const * const WINDOW_NAME{"Multith"};
static int  const         WINDOW_INIT_SIZE_X{800};
static int  const         WINDOW_INIT_SIZE_Y{600};

class WindowHandler
{
public:
    WindowHandler();
    ~WindowHandler();

    void onTick();

private:

    void render();
    void handleInput();

    sf::CircleShape testShape;
    int circleX;
    
    sf::RenderWindow window;
};
