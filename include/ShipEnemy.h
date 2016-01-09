#ifndef SHIPENEMY_H
#define SHIPENEMY_H

#include "Ship.h"
#include "Behavior.h"

class ShipEnemy : public Ship
{
    public:
        ShipEnemy(int nblives);
        ShipEnemy(int nblives, float speed);
        virtual ~ShipEnemy();
        ShipEnemy(ShipEnemy const& ref);
        ShipEnemy& operator=(ShipEnemy const& ref);
        void setVxBehavior(float (*f)(float));
        void setVyBehavior(float (*f)(float));
        void setPointBehavior(std::vector<sf::Vector2f> const& points, bool mode = false);
        virtual void update(float dt);
    protected:
        BehaviorAstract* behavior;
    private:
};

#endif // SHIPENEMY_H
