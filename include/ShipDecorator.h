#ifndef SHIPDECORATOR_H
#define SHIPDECORATOR_H

#include "Utils.h"
#include "Ship.h"
#include "TextureManager.h"

class ShipDecorator : public Ship
{
    public:
        Ship* getBase() const {return &ship;}
        virtual ~ShipDecorator() = 0;
        void hit(int nb);
    protected:
        ShipDecorator(Ship& ref) : ship(ref){}
        Ship& ship;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class ShipShield : public ShipDecorator
{
    public:
        ShipShield(Ship & ref, int def, int defmax);
        ~ShipShield();
        void hit(int nbDamage=1);
        void regen(int nb=1);
        int getDefense() const {return defense;}
        virtual void update(float dt);
    protected:
        static constexpr const float ROTATION_V = 0.1f;
        int defenseMax;
        int defense;
        sf::Sprite img;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

// useless test
class ShipShieldTest : public ShipDecorator
{
    public:
        ShipShieldTest(Ship & ref) : ShipDecorator(ref) {};
        ~ShipShieldTest(){};
    protected:
};

#endif // SHIPDECORATOR_H
