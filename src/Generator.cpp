#include "../include/Generator.h"

Generator::Generator(std::deque<Bullet>* blist):
    bullet(blist),elapsed(0.f),live(1), nblaunch(0), link(NULL)
{

}

Generator::~Generator()
{
    //link = NULL;
}

void Generator::linkTo(Entity* ent)
{
    link = ent;
    sprite.setRotation(link->getSprite().getRotation());
}

void Generator::update(float dt)
{
    if(link != NULL){
        sprite.setPosition(link->getPos()+1.f*sprite.getOrigin());
        //sprite.move(link->getV()*dt);
    }
    elapsed += dt;
    if(elapsed >= rate){
        elapsed -= rate;
        nblaunch++;
        launch();

    }
}

inline void Generator::setStandardBullet(std::string filename)
{
        bullet->back().getSprite().setTexture(*TextureManagerGlobal::getTexture(filename));

        //bullet->back().getSprite().setOrigin(sf::Vector2f(bullet->back().getSprite().getLocalBounds().width/2.f,0.f));
        bullet->back().getSprite().setOrigin(sf::Vector2f(bullet->back().getSprite().getLocalBounds().width/2.f,
                                                               bullet->back().getSprite().getLocalBounds().height/2.f));
        bullet->back().getSprite().setPosition(sprite.getPosition());
        bullet->back().getSprite().move(
            sf::Vector2f(sprite.getLocalBounds().width/2.f,sprite.getLocalBounds().height)/-2.f);
}

inline void Generator::setStandardBullet(std::string filename, int element)
// the bullet has to be added to the list before set standard
{
        TextureManagerGlobal::assignTextureRect(bullet->back().getSprite(),filename,element);

        //bullet->back().getSprite().setOrigin(sf::Vector2f(bullet->back().getSprite().getLocalBounds().width/2.f,0.f));
        bullet->back().getSprite().setOrigin(sf::Vector2f(bullet->back().getSprite().getLocalBounds().width/2.f,
                                                               bullet->back().getSprite().getLocalBounds().height/2.f));
        bullet->back().getSprite().setPosition(sprite.getPosition());
        bullet->back().getSprite().move(
            sf::Vector2f(sprite.getLocalBounds().width/2.f,sprite.getLocalBounds().height)/-2.f);
}

PlayerGenerator::PlayerGenerator(std::deque<Bullet>* bullet_list) :
            Generator(bullet_list)
{
}
