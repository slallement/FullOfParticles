#ifndef COMPOSEDENTITY_H
#define COMPOSEDENTITY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"

class ComposedEntity: public Entity
{
    public:
        ComposedEntity();
        virtual ~ComposedEntity();
    protected:
        std::vector<ComposedEntity*> leaf;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(sprite, states);
            for(std::vector<ComposedEntity*>::const_iterator it=leaf.begin();
                    it!=leaf.end();++it){
                target.draw(**it, states);
            }
        }
    private:
};

#endif // COMPOSEDENTITY_H
