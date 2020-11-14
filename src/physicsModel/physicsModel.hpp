#pragma once

#include <optional>
#include <memory>

#include "./physicsModelPrintable.hpp"
#include "../../multithlib/actor.hpp"
#include "../printer/printer.hpp"

struct PhysicsObject
{
public:
    double posX;
    double posY;
    
    double velX;
    double velY;
    
    void onTick();
    
    PhysicsObjectPrintable generatePrintableCircle(float radius) const;
    PhysicsObjectPrintable generatePrintableSprite(char const * const directory, unsigned int frame) const;
private:
};

class WindowHandler; // to fix some compiler recursion issue
class PhysicsModel
{
public:
    
    PhysicsModel() = default;
    ~PhysicsModel() = default;
    
    void onTick();
    void giveOutboundActors(
        std::weak_ptr<multith::Actor<WindowHandler>> nprinter
    );
    
    void pushPlayer(double pushX, double pushY);
    
private:
    
    struct OutboundActors {
        std::weak_ptr<multith::Actor<WindowHandler>> printer;
    }; std::optional<OutboundActors> outboundActors;
    
    PhysicsObject player;
    
    PhysicsModelPrintable generatePrintable() const;
};
