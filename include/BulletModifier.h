#ifndef BULLETMODIFIER_H
#define BULLETMODIFIER_H

#include "Utils.h"
#include "Entity.h"
#include "Bullet.h"
#include <deque>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

class BulletModifier : public Entity
{
    public:
        BulletModifier(std::deque<Bullet>* bullet_list, float totalduration);
        BulletModifier(std::deque<Bullet>* bullet_list);
        virtual ~BulletModifier() = 0;
        virtual void update(float dt){time+=dt;};
        bool isInactive(){return hasExpired();}
    protected:
        inline bool hasExpired(){return (time>=duration)?((duration>0.f)?true:false)
                                                        :false;};
        std::deque<Bullet>* bullet;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const=0;
        float time;
        float duration;
    private:
};

class Attractor : public BulletModifier
{
    public:
        Attractor(std::deque<Bullet>* bullet_list, float n_radius, sf::Vector2f npos, float power = -60.f, float nduration = -1.f);
        void update(float dt);

    protected:
        sf::Sprite sprite2;
        float radius;
        float strength;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Destroyer : public BulletModifier
{
        public:
        Destroyer(std::deque<Bullet>* bullet_list, float n_radius, sf::Vector2f npos, float power = 70.f, float nduration = 3.f);
        void update(float dt);

    protected:
        sf::Sprite sprite2;
        float radius;
        float strength;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // BULLETMODIFIER_H
