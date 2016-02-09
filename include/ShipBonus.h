#ifndef SHIPBONUS_H
#define SHIPBONUS_H

#include "PlayerShip.h"
#include <stdint.h>

class ShipBonus : public Entity
{
    public:
        enum BONUS{LIFE_LV1=0,SHILED_LV1=1,IMPROVE_RATE1=2};
        ShipBonus();
        ShipBonus(int type);
        void setType(int type);
        void update(float dt);
        void affect(PlayerShip & ship);
        virtual ~ShipBonus();

    protected:
        int16_t type;
    private:
};



#endif // SHIPBONUS_H
