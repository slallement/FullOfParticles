#ifndef MISSIONMANAGER_H
#define MISSIONMANAGER_H

#include <vector>
#include <fstream>

#include "Mission.h"
#include "Game.h"

class MissionFileState
{
    protected:
        int id;
        bool state;

    public :
        MissionFileState(){};
        MissionFileState(int Id, bool State):id(Id),state(State){};
        friend std::ostream& operator<<(std::ostream & os,const MissionFileState &m);
        friend class MissionMenu;
        friend class MissionManager;
};

std::ostream& operator<<(std::ostream & os, const MissionFileState &m);

class MissionManager
{
    public:
        MissionManager();
        bool getMissionState(unsigned int id) const;
        std::string getMissionName(unsigned int id) const;
        void save();
        void load();
        void unlock(unsigned int id);
        unsigned int size() const;
        Mission* createMission(unsigned int id, Game* game);
        // -> return 0 if the mission (id) is lock

        static const int NB_MISSION = 5;
    protected:
        std::vector<MissionFileState> mission;
};

#endif // MISSIONMANAGER_H
