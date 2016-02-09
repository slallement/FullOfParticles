#include "../include/ShipEnemy.h"

ShipEnemy::ShipEnemy(int nlives):
    Ship(nlives,1.f), behavior(new BehaviorFunction(&v))
{
}

ShipEnemy::ShipEnemy(int nlives, float vel):
    Ship(nlives, vel), behavior(new BehaviorFunction(&v))
{
}

ShipEnemy::~ShipEnemy()
{
    delete behavior;
}

/*void ShipEnemy::setBehavior(BehaviorFunction* b)
{
    behavior = b;
}*/

void ShipEnemy::setPointBehavior(std::vector<sf::Vector2f> const& points, bool mode)
{
    delete behavior;
    behavior = new BehaviorLinearPath(&v, points, velocity, mode);
}

void ShipEnemy::setVxBehavior(float (*f)(float))
{
    static_cast<BehaviorFunction*>(behavior)->setFx(f);
}

void ShipEnemy::setVyBehavior(float (*f)(float))
{
    static_cast<BehaviorFunction*>(behavior)->setFy(f);
}

ShipEnemy& ShipEnemy::operator=(const ShipEnemy& copy)
{
    (Ship)*this = copy;
    //timeAlive = 0.f;
    /*fvx = copy.fvx;
    fvy = copy.fvy;*/
    /*v = copy.v;
    vrot = copy.vrot;
    lifeMax = copy.lifeMax;
    life = copy.life;
    velocity = copy.velocity;
    spriteLinkedToV = copy.spriteLinkedToV;
    t1 = 0.f;
    sprite = copy.sprite;
    for(unsigned int i=0;i<copy.weapons.size();i++){
        weapons.push_back(copy.weapons[i]->clone());
        weapons.back()->linkTo(this);
    }*/
    //delete behavior;
    if(copy.behavior){
        behavior = copy.behavior->clone(&v);
    }else{
        behavior = new BehaviorNull();
    }
    return *this;
}

ShipEnemy::ShipEnemy(ShipEnemy const& copy) :
    Ship(copy), behavior(copy.behavior)
{
    if(copy.behavior){
        behavior = (copy.behavior)->clone(&v);
    }else{
        behavior = new BehaviorNull();
    }
}

void ShipEnemy::update(float dt)
{
    behavior->update(dt);
    Ship::update(dt);
}
