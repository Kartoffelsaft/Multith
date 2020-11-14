#include <cassert>

#include "./physicsModel.hpp"
#include "../printer/printer.hpp"
#include "../tickCoordinator/tickCoordinator.hpp"

void PhysicsModel::giveOutboundActors(
    std::weak_ptr<multith::Actor<WindowHandler>> nprinter
){
    outboundActors = {
        nprinter
    };
}

void PhysicsModel::onTick()
{
    player.onTick();
    assert(outboundActors.has_value());
    outboundActors->printer.lock()->call(&WindowHandler::renderPhysicsModel, generatePrintable());
}

void PhysicsObject::onTick()
{
    posX += (velX / TICK_PER_SECOND);
    posY += (velY / TICK_PER_SECOND);
}

void PhysicsModel::pushPlayer(double pushX, double pushY)
{
    player.velX += pushX;
    player.velY += pushY;
}

PhysicsObjectPrintable PhysicsObject::generatePrintableCircle(float radius) const
{return PhysicsObjectPrintable{posX, posY, radius};}

PhysicsObjectPrintable PhysicsObject::generatePrintableSprite(char const * const directory, unsigned int frame) const
{return PhysicsObjectPrintable{posX, posY, directory, frame};}



PhysicsModelPrintable PhysicsModel::generatePrintable() const
{
    PhysicsModelPrintable ret;
    ret.addPrintable(player.generatePrintableSprite("./assets/sprites/spinny.png", 6));
    return ret;
}

