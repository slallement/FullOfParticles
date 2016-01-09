#include "../include/Entity.h"

void Entity::setTexture(sf::Texture const& texture, bool originCenterXAxis)
{
    sprite.setTexture(texture);
    if(originCenterXAxis){
        sprite.setOrigin(sprite.getGlobalBounds().width/2.f,
                         sprite.getGlobalBounds().height/2.f);
    }
}
