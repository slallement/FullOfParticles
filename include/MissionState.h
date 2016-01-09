#ifndef MISSIONSTATE_H
#define MISSIONSTATE_H

#include "ProgressBar.h"
#include "Mission.h"
class Mission;
struct MissionContext;

class MissionState
{
    public:
        enum MissionMode{ENDING=2,NORMAL=0,DEATHMATCH=1,UNKNOWN};
        //MissionState();
        MissionState(Mission* m, MissionState* n);
        virtual ~MissionState();
        void destroy();
        virtual void init();
        virtual void update(float dt=0.f);
        virtual void nextStep();
        MissionMode getMode() const {return mode;}

    protected:
        Mission* mission;
        MissionState* nextMs;
        MissionMode mode;
        const MissionContext* context;
    private:
};

class MissionStateEnd : public MissionState
{
    public:
        MissionStateEnd(Mission* m);
        void nextStep();
        static MissionStateEnd* getState(Mission* m);
        void init();
        void update(float dt);
    protected:
        static MissionStateEnd* ms;
        sf::Texture success_tex;
        sf::Sprite success;
        sf::Shader shader;
};

#endif // MISSIONSTATE_H
