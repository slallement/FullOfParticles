#include "../include/Ship.h"

Ship::Ship(): Entity(),
    lifeMax(3), life(lifeMax), velocity(1.f), t1(0.f), timeAlive(0.f),
    weapons(), vrot(0.f,0.f), spriteLinkedToV(false)
{
}

Ship::Ship(int nblives, float veloc):
    lifeMax(nblives), life(nblives), velocity(veloc), t1(0.f), timeAlive(0.f),
    weapons(),
    vrot(0.f,0.f), spriteLinkedToV(false)
{
}

Ship::Ship( int nblives, float veloc, std::string imagefile):
    lifeMax(nblives), life(nblives),velocity(veloc), t1(0.f), timeAlive(0.f),
    weapons(),
    vrot(0.f,0.f), spriteLinkedToV(false)
{
    setTexture(*TextureManagerGlobal::getTexture(imagefile),true);
}

Ship::Ship(int nblives, std::string imagefile):
    lifeMax(nblives), life(nblives), velocity(1.f), t1(0.f), timeAlive(0.f),
    vrot(0.f,0.f), spriteLinkedToV(false)
{
    setTexture(*TextureManagerGlobal::getTexture(imagefile),true);
}

Ship::Ship(int nblives, sf::Texture const& texture) :
    lifeMax(nblives), life(nblives), velocity(1.f), t1(0.f), timeAlive(0.f),
    vrot(0.f,0.f), spriteLinkedToV(false)
{
    setTexture(texture,true);
}

Ship::Ship(Ship const& copy) :
    Entity(*this), lifeMax(copy.lifeMax), life(copy.life), velocity(copy.velocity),
    t1(0.f), timeAlive(0.f),
    weapons(), vrot(copy.vrot),spriteLinkedToV(copy.spriteLinkedToV)
{
    sprite = copy.sprite;
    v = copy.getV();
    //weapons.resize(copy.weapons.size());
    for(unsigned int i=0;i<copy.weapons.size();i++){
        weapons.push_back(copy.weapons[i]->clone());
        weapons.back()->linkTo(this);
    }
}

Ship& Ship::operator=(const Ship& copy)
{
    timeAlive = 0.f;
    v = copy.v;
    vrot = copy.vrot;
    lifeMax = copy.lifeMax;
    life = copy.life;
    velocity = copy.velocity;
    spriteLinkedToV = copy.spriteLinkedToV;
    t1 = 0.f;
    sprite = copy.sprite;
    weapons.resize(copy.weapons.size());
    for(unsigned int i=0;i<copy.weapons.size();i++){
        weapons.push_back(copy.weapons[i]->clone());
        weapons.back()->linkTo(this);
    }
    return *this;
}

void Ship::addWeapon(Generator* weapon)
{
    weapons.push_back(weapon);
    weapons.back()->getSprite().setPosition(sprite.getPosition());
    weapons.back()->linkTo(this);
}

void Ship::clearWeapon()
{
    for(int i=0;i<(int)weapons.size();++i){
        delete weapons[i];
        weapons[i] = 0;
    }
}

/*void Ship::hit()
{
    life--;
    sprite.setColor(sf::Color(128,128,128,128));
    t1 = 1.f;
}*/

void Ship::hit(int damages)
{
    if((int)life>=damages)
        life-=damages;
    else
        life = 0;
    sprite.setColor(sf::Color(128,128,128,128));
    t1 = 1.f;
}

void Ship::setStateHit()
{
    sprite.setColor(sf::Color(128,128,128,128));
    t1 = 1.f;
}

void Ship::setRotation(float a)
{
    sprite.setRotation(a);
}

void Ship::rotate(float a)
{
    sprite.rotate(a);
}

sf::Vector2f Ship::getV() const
{
    return (vrot.x!=0 && vrot.y!=0) ? vrot : v;
}

float Ship::getVelocity() const{return velocity;}

void Ship::clampV()
{
    if(v.x>velocity)
        v.x = velocity;
    if(v.x<-velocity)
        v.x = -velocity;
    if(v.y>velocity)
        v.y = velocity;
    if(v.y<-velocity)
        v.y = -velocity;
}

void Ship::update(float dt){
    timeAlive += dt;
    updateMovement(dt);
    updateWeapons(dt);
    updateOther(dt);
}

void Ship::updateMovement(float dt)
{
    if(spriteLinkedToV){
        const float a = cos(sprite.getRotation()*DEG_TO_RAD);
        const float b = sin(sprite.getRotation()*DEG_TO_RAD);
        vrot.x = v.x*a-v.y*b;
        vrot.y = v.y*a+v.x*b;
        sprite.move(dt*vrot);
    }else{
        sprite.move(dt*v);
    }
}
void Ship::updateWeapons(float dt)
{
    for(unsigned int i=0;i<weapons.size();i++){
        //weapons[i]->getSprite().move(v*dt);
        weapons[i]->update(dt);
    }
}
void Ship::updateOther(float dt)
{
    // time of flickering after a hit
    if(t1>0.f){
        t1-=dt;
        if(static_cast<int>(t1*10)%2 ){
            sprite.setColor(sf::Color(128,128,128,128));
        }else{
            sprite.setColor(sf::Color(128,128,128,255));
        }

        if(t1<=0.f){
            sprite.setColor(sf::Color(255,255,255));
        }
    }
}

Ship::~Ship()
{
    clearWeapon();
}

void Ship::setPosition(float x, float y)
{
    sprite.setPosition(x,y);
    for(unsigned int i=0;i<weapons.size();i++){
        weapons[i]->getSprite().setPosition(x,y);
    }
}

void Ship::setPosition(sf::Vector2f nv)
{
    setPosition(nv.x,nv.y);
}

void Ship::addLife(int nb){
    life += nb;
    if(life > lifeMax){
        life = lifeMax;
    }
}
