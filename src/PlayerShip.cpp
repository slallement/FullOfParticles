#include "../include/PlayerShip.h"

const float PlayerShip::BASE_SPEED = 280.f;
const int PlayerShip::BASE_LIFE = 3;
const unsigned int PlayerShip::BASE_SHIELD = 1;
const unsigned int PlayerShip::BASE_SHIELD_MAX = 5;
const sf::IntRect PlayerShip::POS_LEFT = sf::IntRect(100,0,50,50);
const sf::IntRect PlayerShip::POS_MIDDLE = sf::IntRect(50,0,50,50);
const sf::IntRect PlayerShip::POS_RIGHT = sf::IntRect(0,0,50,50);

PlayerShip::PlayerShip() :
    Ship(BASE_LIFE, BASE_SPEED), equipment(0), shiled(0), shiled2(0), focused(false)
{
    init();
}

PlayerShip::PlayerShip(int nblife) :
    Ship(nblife, BASE_SPEED), equipment(0), shiled(0), shiled2(0), focused(false)
{
    init();
}

PlayerShip::PlayerShip(PlayerShip const& copy):
    Ship(copy), equipment(0), focused(false)
{
}

PlayerShip& PlayerShip::operator=(const PlayerShip& copy)
{
    shiled = new ShipShield(*copy.shiled);
    setEquipment();
    return *this;
}

PlayerShip::~PlayerShip()
{
    delete shiled;
    delete shiled2;
    //delete equipment; <- equipment is destroyed automatically
}

ShipShield* PlayerShip::getShiled()
{
    return shiled;
    //return static_cast<ShipShield*>(equipment)->getDefense();
    //return static_cast<ShipShield*>(equipmentref)->getDefense();
}

Ship* PlayerShip::getEquipment()
{
    return equipment;
}

void PlayerShip::focus()
{
    focused = true;
}

void PlayerShip::unfocus()
{
    focused = false;
}

inline void PlayerShip::init()
{
    sprite.setTexture(
            *TextureManagerGlobal::getTexture("ressources/img_ship/shipp1.png"),true);
    sprite.setTextureRect(POS_MIDDLE);
    setRotation(180.f);
    sprite.setOrigin(sprite.getGlobalBounds().width/2.f,0.f);

    shiled = new ShipShield(*this, BASE_SHIELD,BASE_SHIELD_MAX);
    equipment = shiled;
    /*shiled2 = new ShipShieldTest(*equipment);
    equipment = shiled2;*/
    //setEquipment();
    //equipment = shiled;
}

inline void PlayerShip::setEquipment()
{
    equipment = shiled2;
}

void PlayerShip::setBaseWeapon(std::deque<Bullet> & bulletPlayer)
{
    /*weaponsP.push_back(new Generator1p(&bulletPlayer,0.1f,1));
    addWeapon(weaponsP.back());*/
    addWeapon(new Generator2p(&bulletPlayer,0.07f,3,20.f));
    //addWeapon(new Generator3(&bulletPlayer));
}

void PlayerShip::update(float dt)
{
    if(focused){
        timeAlive += dt;
        updateMovement(0.5f*dt);
        updateWeapons(2.0f*dt);
        updateOther(dt);
    }else{
        Ship::update(dt);
    }
}

void PlayerShip::move(float x, float y)
{
    if(x != 0.f){
        if(x > 0.f){
            //right
            v.x = velocity;
            sprite.setTextureRect(POS_RIGHT);
        }else{
            //left
            v.x = -velocity;
            sprite.setTextureRect(POS_LEFT);
        }
    }
    if(y != 0.f){
        v.y = fsign(y)*velocity;
    }
    if(y != 0.f && x != 0.f){
        static const float inv_sqrt_2 = 1.f/sqrtf(2.f);
        v *= inv_sqrt_2;
    }
}

void PlayerShip::stop(bool x){
    if(x){
        v.x = 0.f;
        sprite.setTextureRect(POS_MIDDLE);
    }else
        v.y = 0.f;
}

void PlayerShip::improveWeapon(int mode, int f)
{
    static_cast<PlayerGenerator*>(weapons.back())->improve(mode,f);
}

void PlayerShip::hit(int damages)
{
    // the time of flickering after a hit for the player give invincibilty
    if(t1 > 0.f){
        return;
    }
    if((int)life>=damages)
        life-=damages;
    else
        life = 0;
    sprite.setColor(sf::Color(128,128,128,128));
    t1 = 1.f;
}
