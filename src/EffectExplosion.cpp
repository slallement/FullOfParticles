#include "../include/EffectExplosion.h"
#include "../include/Utils.h"
#include <cmath>
#include <iostream>

ExplosionParticle::ExplosionParticle(float tAlive):
        sprite(), time(0.f), v(), timeAlive(tAlive)
{
    int green = rand()%200+55;
    sprite.setColor(sf::Color(255,green,28));
}

// on update the particle go in the direction of v and disappear progressively
void ExplosionParticle::update(float dt)
{
    if(time+dt <= timeAlive){
        time+=dt;
        sprite.move(v*dt);
        float alpha = 250.f*(1.f-time/timeAlive);
        sprite.setColor(sf::Color(sprite.getColor().r,
                                  sprite.getColor().g,
                                  sprite.getColor().b,(int)alpha));
    }
}

// ----------------------------------------------------------------------------

EffectExplosion::EffectExplosion():
    Entity(), alive(true), time(0.f), t1(T_GEN_PARTICLE), radius(1.f), part()
{
    sprite.setColor(sf::Color(200,200,200,255));
}

EffectExplosion::EffectExplosion(sf::Vector2f pos,const sf::Texture & text):
    Entity(), alive(true), time(0.f), t1(T_GEN_PARTICLE), radius(1.f), part()
{
    setTexture(text,true);
    sprite.setPosition(pos);
    sprite.setColor(sf::Color(200,200,200,255));
    radius = (sprite.getGlobalBounds().height
              +sprite.getGlobalBounds().width)/2.f;
}

EffectExplosion::~EffectExplosion()
{
}

void EffectExplosion::update(float dt)
{
    if(time > T_ALIVE+T_LIVE_PARTICLE){
        if(alive){
            part.clear();
        }
        alive = false;
        return;
    }
    t1 += dt;
    time += dt;
    if(t1 >= T_GEN_PARTICLE){
        for(int i=0;i<NB_PART_RATE;i++){
            addParticle();
            //std::cout<<"ok";
        }
        t1 = 0;
    }
    for(std::deque<ExplosionParticle>::iterator it=part.begin();
                it!=part.end();++it)
    {
        it->update(dt);
    }
}

void EffectExplosion::addParticle()
{
    ExplosionParticle temp(T_LIVE_PARTICLE);
    TextureManagerGlobal::assignTextureRect(
                                temp.sprite,"ressources/img/bullets1.png",4);
    float angle = TWO_PI*(float)rand()/(float)RAND_MAX;
    float t = (float)rand()/(float)RAND_MAX;
    float tempv = 50.f+radius*15.f*t+(t>0.90f?150.f*t:0.f); // final velocity
                                                      // a bit random
    const float SIZE_MIN = 0.2f;
    float size = SIZE_MIN+(1.f-SIZE_MIN)*(1.f-t);
    temp.sprite.setScale(size,size);
    temp.v.x = cos(angle);
    temp.v.y = sin(angle);
    sf::Vector2f dev = -temp.v*radius/2.f;
    temp.v *= tempv;
    temp.sprite.setPosition(sprite.getPosition()+dev);

    part.push_back(temp);
}

void EffectExplosion::draw(sf::RenderTarget& target,
                           sf::RenderStates states) const
{
    target.draw(sprite, states);
    for(std::deque<ExplosionParticle>::const_iterator it=part.begin();
        it!=part.end();++it)
    {
        if(it->time < it->timeAlive){
            target.draw(it->sprite);
        }
    }
}

bool EffectExplosion::isActive() const
{
    return alive;
}

