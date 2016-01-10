#ifndef MAINMENU_H
#define MAINMENU_H

#include "Game.h"
#include "BigImage.h"
#include "Utils.h"
#include <vector>
#include <list>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "MissionMenu.h"
#include "OptionMenu.h"

class MainMenu : public Menu
{
    public:
        MainMenu(sf::RenderWindow & window);
        virtual void update(float dt);
        virtual ~MainMenu();

        void runGame();
        void visualize();
        void learningMode();
        void exit();
        void mode();

    protected:
        virtual void initPosition();
        virtual void loadBackground();
        virtual void drawMenu();

        sf::Clock elapsed;
        sf::Shader shad_blur;
        sf::Sprite title;

    private:
};

#endif // MAINMENU_H
