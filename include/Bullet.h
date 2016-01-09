#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Bullet : public Entity
{
    public:
        Bullet();
        //virtual ~Bullet();
        ~Bullet();
        void update(float dt);
    protected:

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(sprite, states);
        }

};

#endif // BULLET_H
