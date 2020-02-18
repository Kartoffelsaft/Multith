#include "./physicsModelPrintable.hpp"

PhysicsObjectPrintable::PhysicsObjectPrintable(
    double nposX, 
    double nposY, 
    float nradius
) : posX{nposX},
    posY{nposY},
    type{
        .typeEnum = Type::Circle,
        .typeData = {.circle = {nradius}}
    }
{}


PhysicsObjectPrintable::PhysicsObjectPrintable(
    double nposX, 
    double nposY, 
    char const * const ndirectory
) : posX{nposX}, 
    posY{nposY}, 
    type{
        .typeEnum = Type::Sprite,
        .typeData = {.sprite = {ndirectory}}
    }
{}

void PhysicsModelPrintable::addPrintable(PhysicsObjectPrintable nprintable)
{printables.push_back(nprintable);}

void PhysicsModelPrintable::addToWindow(sf::RenderWindow* window)
{
    for(auto printable : printables)
    {
        switch(printable.type.typeEnum)
        {
            case PhysicsObjectPrintable::Type::Circle:
            {
                sf::CircleShape ncircle{printable.type.typeData.circle.radius};
                ncircle.setPosition(printable.posX, printable.posY);
                ncircle.setFillColor(sf::Color::Green); // TODO: Parameterize
                window->draw(ncircle);
                break;
            }
                
            case PhysicsObjectPrintable::Type::Sprite:
            {
                // TODO: Implement
                break;
            }
        }
    }
}
