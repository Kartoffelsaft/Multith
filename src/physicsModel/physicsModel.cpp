#include <cassert>

#include "./physicsModel.hpp"
#include "../printer/printer.hpp"

void PhysicsModel::giveOutboundActors(
    std::weak_ptr<Actor<WindowHandler>> nprinter
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
    posX += velX;
    posY += velY;
}

void PhysicsModel::pushPlayer(double pushX, double pushY)
{
    player.velX += pushX;
    player.velY += pushY;
}

PhysicsObjectPrintable PhysicsObject::generatePrintableCircle(float radius) const
{
    return PhysicsObjectPrintable{posX, posY, radius};
}


PhysicsModelPrintable PhysicsModel::generatePrintable() const
{
    PhysicsModelPrintable ret;
    ret.addPrintable(player.generatePrintableCircle(5));
    return ret;
}

