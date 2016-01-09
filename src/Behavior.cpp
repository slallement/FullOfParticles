#include "../include/Behavior.h"

BehaviorAstract::BehaviorAstract(sf::Vector2f* ref):
    var(ref), timeAlive(0.f)
{

}

BehaviorAstract::BehaviorAstract(const BehaviorAstract& copy):
    var(copy.var), timeAlive(0.f)
{

}

BehaviorAstract::BehaviorAstract(const BehaviorAstract& , sf::Vector2f* ref):
    var(ref), timeAlive(0.f)
{

}

BehaviorAstract& BehaviorAstract::operator=(const BehaviorAstract& copy)
{
    var = copy.var;
    timeAlive = 0.f;
    return *this;
}


BehaviorAstract::~BehaviorAstract()
{
}

void BehaviorAstract::update(float)
{
}

//--

BehaviorFunction::BehaviorFunction(sf::Vector2f* ref,
        float (*functionX)(float), float (*functionY)(float) ):
    BehaviorAstract(ref), fx(functionX), fy(functionY)
{

}

BehaviorFunction::BehaviorFunction(sf::Vector2f* ref):
    BehaviorAstract(ref), fx(0), fy(0)
{
}

BehaviorFunction::BehaviorFunction(const BehaviorFunction& copy, sf::Vector2f* ref):
    BehaviorAstract(ref), fx(copy.fx), fy(copy.fy)
{
}

BehaviorFunction& BehaviorFunction::operator=(const BehaviorFunction& copy)
{
    fx = copy.fx;
    fy = copy.fy;
    var = copy.var;
    timeAlive = 0.f;
    return *this;
}

BehaviorFunction* BehaviorFunction::clone(sf::Vector2f* ref) const
{
     return new BehaviorFunction( *this, ref );
}

void BehaviorFunction::update(float dt)
{
    timeAlive += dt;
    if(fx){
        var->x = fx(timeAlive);
    }
    if(fy){
        var->y = this->fy(timeAlive);
    }
}

void BehaviorFunction::setFx(float (*f)(float))
{
    fx = f;
}
void BehaviorFunction::setFy(float (*f)(float))
{
    fy = f;
}


//---

BehaviorLinearPath* BehaviorLinearPath::clone(sf::Vector2f* ref) const
{
    return new BehaviorLinearPath( *this, ref );
}

 BehaviorLinearPath::BehaviorLinearPath(const BehaviorLinearPath& copy, sf::Vector2f* ref) :
    BehaviorAstract(*this,ref), current(copy.current), points(copy.points),
    d(copy.d), v(copy.v), mode(copy.mode)
{

}

BehaviorLinearPath::BehaviorLinearPath(sf::Vector2f* ref,
        std::vector<sf::Vector2f> const& p, float vel, bool timeCste):
    BehaviorAstract(ref), current(0), points(p), d(), v(vel), mode(timeCste)
{
    // if mode = false : v = velocity (constant) thus d contain d/v
    // if mode = true : v = time (constant) thus d contain d/t

    if(!mode){
        unsigned int size = p.size();
        d.resize(size+1);
        for(unsigned int i=0;i<size;i++){
            d[i] = sqrt(p[i].x*p[i].x+p[i].y*p[i].y)/vel;
            d[size] += d[i];
        }
    }
}

BehaviorLinearPath::BehaviorLinearPath(sf::Vector2f* ref):
    BehaviorAstract(ref), current(0), points(), d(), v(0.f), mode(false)
{

}

void BehaviorLinearPath::update(float dt)
{

    if(!mode){ // v = velocity cste
        if(timeAlive >= d[current]){
            timeAlive -= d[current];
            current++;
            if(current > d.size()-2){
                current = 0;
            }
        }
        var->x = points[current].x/d[current];
        var->y = points[current].y/d[current];
    }else{
        if(timeAlive >= v){
            timeAlive -= v;
            current++;
            if(current > points.size()-1){
                current = 0;
            }
        }
        var->x = points[current].x/v;
        var->y = points[current].y/v;
    }
    //
    timeAlive += dt;
}

