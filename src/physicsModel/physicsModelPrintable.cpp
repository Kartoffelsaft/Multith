#include "./physicsModelPrintable.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

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
    char const * const ndirectory,
    unsigned int frames
) : posX{nposX}, 
    posY{nposY}, 
    type{
        .typeEnum = Type::Sprite,
        .typeData = {.sprite = {ndirectory, frames}}
    }
{}

void PhysicsModelPrintable::addPrintable(PhysicsObjectPrintable nprintable)
{printables.push_back(nprintable);}

void PhysicsModelPrintable::addToWindow(sf::RenderTarget* window, unsigned long long const frame)
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
                sf::Sprite nsprite;
                nsprite.setPosition(printable.posX, printable.posY);
                nsprite.setTexture(*textureCache.loadTexture(printable.type.typeData.sprite.directory));
                auto rect = nsprite.getTextureRect();
                rect.width /= printable.type.typeData.sprite.frames;
                rect.left += rect.width * (frame % printable.type.typeData.sprite.frames);
                nsprite.setTextureRect(rect);
                window->draw(nsprite);
                break;
            }
        }
    }
}

sf::Texture* TextureCache::loadTexture(char const * const directory)
{
    if(textureHash.count(directory))
    {
        return &textureHash.at(directory);
    }
    else
    {
        sf::Texture newTexture;
        newTexture.loadFromFile(directory);
        textureHash[directory] = newTexture;
        return &textureHash[directory];
    }
}
