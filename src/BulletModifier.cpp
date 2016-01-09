#include "../include/BulletModifier.h"

BulletModifier::BulletModifier(std::deque<Bullet>* bullet_list, float nduration) :
    bullet(bullet_list), time(0.f), duration(nduration)
{

}

BulletModifier::BulletModifier(std::deque<Bullet>* bullet_list) :
    bullet(bullet_list), time(0.f), duration(-1.f)
{

}

BulletModifier::~BulletModifier()
{
    //dtor
}

// ----------------------------------------------------------------------------

Attractor::Attractor(std::deque<Bullet>* bullet_list, float n_radius,
        sf::Vector2f npos, float nstrength, float nduration) :
    BulletModifier(bullet_list, nduration), sprite2(),
    radius(n_radius), strength(nstrength)
{
    sprite.setPosition(npos);

    sprite.setTexture(*TextureManagerGlobal::getTexture("ressources/img2/circleBorder1.png"));
    if(sprite.getTextureRect().width != 0){
        sprite.setOrigin(sprite.getTextureRect().width/2,sprite.getTextureRect().width/2);
        sprite.scale(radius*2/sprite.getTextureRect().width,
                 radius*2/sprite.getTextureRect().width);
        sprite.setColor(sf::Color(255,255,255,190));
    }

    sprite2.setPosition(npos);
    sprite2.setTexture(*TextureManagerGlobal::getTexture("ressources/img2/circleBorder1inside.png"));
    if(sprite2.getTextureRect().width != 0){
        sprite2.setOrigin(sprite2.getTextureRect().width/2,sprite2.getTextureRect().width/2);
        sprite2.scale(radius*2/sprite2.getTextureRect().width,
                 radius*2/sprite2.getTextureRect().width);
        sprite2.setColor(sf::Color(255,255,255,100));
    }

}

void Attractor::update(float dt)
{
    BulletModifier::update(dt);
    if(hasExpired())
        return;
    for(unsigned int i=0;i<bullet->size(); i++){
        sf::Vector2f bpos((*bullet)[i].getSprite().getPosition());
        if( Utils::inCircle(bpos, sprite.getPosition(), radius)){
            sf::Vector2f fact = strength*(sprite.getPosition()-bpos)*dt;
            (*bullet)[i].addV(fact);
            (*bullet)[i].getSprite().setRotation(
                ((*bullet)[i].getSprite().getRotation()*1.f
                + RAD_TO_DEG*atan2((*bullet)[i].getV().y,(*bullet)[i].getV().x))/2.f );
        }
    }
    sprite.rotate(40.f*dt);
    sprite2.rotate(-30.f*dt);
}

void Attractor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    /*sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(80, 250, 250,100));
    circle.setOrigin(radius,radius);
    states.blendMode = sf::BlendMultiply;*/
    //target.draw(circle, states.transform.combine(sprite.getTransform()));
    target.draw(sprite, states);
    target.draw(sprite2, states);
}

// ----------------------------------------------------------------------------

Destroyer::Destroyer(std::deque<Bullet>* bullet_list, float n_radius,
        sf::Vector2f npos, float nstrength, float nduration) :
    BulletModifier(bullet_list, nduration), sprite2(),
    radius(n_radius), strength(nstrength)
{
    sprite.setPosition(npos);

    sprite.setTexture(*TextureManagerGlobal::getTexture("ressources/img2/circleBorder2.png"));
    if(sprite.getTextureRect().width != 0){
        sprite.setOrigin(sprite.getTextureRect().width/2,sprite.getTextureRect().width/2);
        sprite.scale(radius*2/sprite.getTextureRect().width,
                 radius*2/sprite.getTextureRect().width);
        sprite.setColor(sf::Color(255,255,255,190));
    }

    sprite2.setPosition(npos);
    sprite2.setTexture(*TextureManagerGlobal::getTexture("ressources/img2/circleBorder2inside.png"));
    if(sprite2.getTextureRect().width != 0){
        sprite2.setOrigin(sprite2.getTextureRect().width/2,sprite2.getTextureRect().width/2);
        sprite2.scale(radius*2/sprite2.getTextureRect().width,
                 radius*2/sprite2.getTextureRect().width);
        sprite2.setColor(sf::Color(255,255,255,100));
    }

    strength *= 70.f;
}

void Destroyer::update(float dt)
{
    BulletModifier::update(dt);
    if(hasExpired())
        return;
    for(unsigned int i=0;i<bullet->size(); i++){
        sf::Vector2f bpos((*bullet)[i].getSprite().getPosition());
        if( Utils::inCircle(bpos, sprite.getPosition(), radius)){
            float d = fabs((*bullet)[i].getV().x)+
                    fabs((*bullet)[i].getV().y);
            if( d < strength){
                bullet->erase(bullet->begin()+i);
                --i;
            }
        }
    }
    sprite.rotate(40.f*dt);
    sprite2.rotate(-30.f*dt);
}

void Destroyer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    target.draw(sprite2, states);
}
