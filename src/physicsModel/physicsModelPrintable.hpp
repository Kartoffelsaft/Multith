#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <map>

struct PhysicsObjectPrintable
{
public:
    
    double posX, posY;
    struct Type 
    {
        enum TypeEnum {
            Circle,
            Sprite,
        } typeEnum;
        union TypeData
        {
            struct 
            {
                float radius;
            } circle;
            struct
            {
                char const * const directory;
                unsigned int frames;
            } sprite;
        } typeData;
    } type;
    
    PhysicsObjectPrintable( // circle constructor
        double nposX,
        double nposY,
        float nradius
    );
    
    PhysicsObjectPrintable( // sprite constructor
        double nposX, 
        double nposY, 
        char const * const ndirectory,
        unsigned int frames
    );
    
    ~PhysicsObjectPrintable() = default;
    
private:
};

class PhysicsModelPrintable
{
public:
    
    void addPrintable(PhysicsObjectPrintable nprintable);
    void addToWindow(sf::RenderWindow* window, unsigned long long const frame);
    
private:
    
    std::vector<PhysicsObjectPrintable> printables;
};

static thread_local struct TextureCache
{
public:
    
    TextureCache() = default;
    
    sf::Texture* loadTexture(char const * const directory);
    
private:
    
    std::map<char const *, sf::Texture> textureHash;
} textureCache;
