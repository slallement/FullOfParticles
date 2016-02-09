#ifndef SHIP_H
#define SHIP_H

#include "Generator.h"
#include "Entity.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Ship : public Entity
{
    public:
        Ship();
        Ship(Ship const& copy);
        Ship& operator=(const Ship& copy);
        Ship(int nblives, float velocity);
        Ship(int nblives, std::string imagefile);
        Ship(int nblives, float velocity, std::string imagefile);
        Ship(int nblives, sf::Texture const& texture);
        virtual ~Ship();
        void setVxBehavior(float (*function)(float));
        void setVyBehavior(float (*function)(float));
        float getVelocity() const;

        void addWeapon(Generator* weapon);
        void clearWeapon();
        unsigned int getLives() const {return life;}
        unsigned int getLivesMax() const {return lifeMax;}
        sf::Vector2f getV() const;
        void clampV();
        void setPosition(float x, float y);
        void setPosition(sf::Vector2f pos);
        void rotate(float angle);
        void setRotation(float angle);
        void linkSpriteRotation(bool choice=true){spriteLinkedToV = choice;}
        float getTimeLastHit()const{return t1;}
        void addLife(int lnLives=1);
        virtual void hit(int damages=1);
        virtual void update(float dt);
        /*void setV(float x,float y){v.x=x;v.y=y;}
        void setV(sf::Vector2f nv){v=nv;}*/
    protected:
        void setStateHit();
        void updateMovement(float dt);
        void updateWeapons(float dt);
        void updateOther(float dt);
        unsigned int lifeMax;
        unsigned int life;
        float velocity;
        float t1;
        float timeAlive;
        std::vector<Generator*> weapons;
        sf::Vector2f vrot;
        bool spriteLinkedToV;
    private:

    friend class ShipDecorator;
};

#endif // SHIP_H
