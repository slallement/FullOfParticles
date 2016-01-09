#ifndef MISSIONMENU_H
#define MISSIONMENU_H

#include "Menu.h"
#include "MissionManager.h"

class MissionMenu: public Menu
{
    public:
        MissionMenu(sf::RenderWindow & window);
        virtual ~MissionMenu();
        virtual void update(float dt);
        virtual void startMission();
        void syncProgressFile();
        void updateProgressFile();
        void makeMenu();

    protected:
        virtual void initPosition();
        virtual void loadBackground();

        Game* game;
        MissionManager missions;
        int offset;
        sf::Clock elapsed;
    private:
};

#endif // MISSIONMENU_H
