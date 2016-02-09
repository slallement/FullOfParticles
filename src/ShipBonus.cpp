#include "../include/ShipBonus.h"
#include "../include/TextureManager.h"
#include "../include/Generator.h"

ShipBonus::ShipBonus()
{
    //ctor
}

ShipBonus::~ShipBonus()
{
    //dtor
}

ShipBonus::ShipBonus(int t)
{
    setType(t);
}

void ShipBonus::setType(int t)
{
    type = t;
    sprite.setTexture(*TextureManagerGlobal::getTexture("ressources/img2/bonus1.png"));
    sprite.setTextureRect(TextureManagerGlobal::getTextureRectBonus(type));
    setVy(100.f);
}

void ShipBonus::update(float dt)
{
    sprite.move(dt*v);
}

void ShipBonus::affect(PlayerShip & s)
{
    if(type == LIFE_LV1){
        s.addLife();
    }else if(type == SHILED_LV1){
        s.getShiled()->regen();
    }else if(type == IMPROVE_RATE1){
        s.improveWeapon(PlayerGenerator::RATE);
    }
}
