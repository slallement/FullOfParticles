#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <deque>
#include "Bullet.h"
#include "Utils.h"
#include "Entity.h"

class Generator : public Entity
{
    public:
        Generator(std::deque<Bullet>* bullet_list);
        virtual ~Generator();
        void update(float dt);
        virtual void launch() = 0;
        //sf::Sprite sprite;
        void linkTo(Entity* ent);
        virtual Generator* clone() const = 0;
    protected:
        virtual void setStandardBullet(std::string filename);
        virtual void setStandardBullet(std::string filename, int element);
        std::deque<Bullet>* bullet;
        float elapsed;
        float rate; // time before each launch
        int live;
        int nblaunch; // number of launch
        int n;
        Entity* link; // not dynamically allocated
    private:
        static int nbArg[];
};

class PlayerGenerator : public Generator
{
    public:
        enum MODE{RATE=1};
        PlayerGenerator(std::deque<Bullet>* bullet_list);
        virtual void improve(int mode, int factor = 1) = 0;
    protected:

};

#endif // GENERATOR_H
