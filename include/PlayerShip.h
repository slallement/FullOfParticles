#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <deque>
#include "Ship.h"
#include "ShipDecorator.h"
#include "Generator.h"
#include "GeneratorPreset.h"

class PlayerShip : public Ship
{
    public:
        PlayerShip();
        PlayerShip(int nbLife);
        PlayerShip(PlayerShip const& copy);
        PlayerShip& operator=(const PlayerShip& copy);
        void setBaseWeapon(std::deque<Bullet> & bulletPlayer);
        virtual ~PlayerShip();
        virtual void update(float dt);
        void improveWeapon(int mode, int f=1);
        void focus();
        void unfocus();
        Ship* getEquipment();
        //int getDefense();
        ShipShield* getShiled();
        void move(float x, float y);
        void stop(bool x);
        virtual void hit(int damages=1);
    protected:
        void init();

        Ship* equipment;
        ShipShield* shiled;
        ShipShieldTest* shiled2;
        std::deque<PlayerGenerator*> weaponsP;
        bool focused;

        static const float BASE_SPEED;
        static const int BASE_LIFE;
        static const sf::IntRect POS_MIDDLE;
        static const sf::IntRect POS_LEFT;
        static const sf::IntRect POS_RIGHT;
        static const unsigned int BASE_SHIELD;
        static const unsigned int BASE_SHIELD_MAX;
    private:
        void setEquipment();
};



#endif // PLAYERSHIP_H
