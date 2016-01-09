#include "../include/ShipDecorator.h"

void ShipDecorator::draw(sf::RenderTarget& target,
                         sf::RenderStates states) const
{
    target.draw(ship, states);
}

void ShipDecorator::hit(int nb){ship.hit(nb);}

ShipDecorator::~ShipDecorator() {}

// -----------------------------------------------------------------------------

ShipShield::ShipShield(Ship & ref, int def, int defmax) :
    ShipDecorator(ref),
    defenseMax(defmax), defense(def)
{
    img.setTexture(*TextureManagerGlobal::getTexture("ressources/img2/shiled.png"));
    img.setOrigin(img.getTextureRect().width/2.f,img.getTextureRect().height/2.f);
    img.move(ref.getSprite().getTextureRect().width/2.f,ref.getSprite().getTextureRect().height/2.f);
}

ShipShield::~ShipShield(){}

void ShipShield::hit(int nb)
{
    if(defense >= nb){
        defense -= nb;
        t1 = 1.f;
    }else{
        ship.hit(nb-defense);
        //Ship::hit(nb-defense);
        defense = 0;
    }
}

void ShipShield::regen(int nb){
    if(defense+nb<defenseMax){
        defense += nb;
    }else{
        defense = defenseMax;
    }
}

#include <iostream>

void ShipShield::update(float dt)
{
    if(t1>0.f){
        t1-=dt;
        if(static_cast<int>(t1*10)%2 ){
            img.setColor(sf::Color(128,128,128,128));
        }else{
            img.setColor(sf::Color(128,128,128,255));
        }

        if(t1<=0.f){
            img.setColor(sf::Color(255,255,255));
        }
    }
    ship.update(dt);
    img.rotate(dt*ROTATION_V*RAD_TO_DEG*TWO_PI);
}

void ShipShield::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    //target.draw(ship.getSprite(), states);
    ShipDecorator::draw(target,states);
    if(defense){
        sf::Transform t;// t.translate(ship.getSprite().getPosition());
        t.combine(ship.getSprite().getTransform());
        target.draw(img,t);
    }
    //target.draw(ship.getSprite(), states);

}


