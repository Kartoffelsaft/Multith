#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

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
        char const * const ndirectory
    );
    
    ~PhysicsObjectPrintable() = default;
    
private:
};

class PhysicsModelPrintable
{
public:
    
    void addPrintable(PhysicsObjectPrintable nprintable);
    void addToWindow(sf::RenderWindow* window);
    
private:
    
    std::vector<PhysicsObjectPrintable> printables;
};
