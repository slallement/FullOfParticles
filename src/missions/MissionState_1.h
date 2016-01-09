#ifndef MISSION_1_H
#define MISSION_1_H

#include "MissionState.h"

class MissionState1_1 : public MissionState
{
    public:
        MissionState1_1(Mission* m, MissionState* n);
        virtual void init();
        virtual void update(float dt);
    protected:
        TextureManager textures;
        const float begin;
        float a1,d1,a2, d2;
        sf::Texture splash_tex;
        sf::Sprite splash1;
        sf::Sprite splash2;
};

class MissionState1_2 : public MissionState
{
    public:
        MissionState1_2(Mission* m, MissionState* n);
        virtual void init();
        virtual void update(float dt);
    protected:
        TextureManager textures;
        int initialLives;
        ProgressBar lifebar;
};

#endif

