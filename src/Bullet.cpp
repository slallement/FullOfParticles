#include "../include/Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::update(float dt){
    sprite.move(v*dt);
}
