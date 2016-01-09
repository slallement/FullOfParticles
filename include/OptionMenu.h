#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include "Game.h"
#include "BigImage.h"
#include "Utils.h"
#include <vector>
#include <list>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "MissionMenu.h"

class OptionMenu : public Menu
{
    public:
        OptionMenu(sf::RenderWindow & window);
        virtual ~OptionMenu();
    protected:
        virtual void initPosition();
        void changeResolution();
        int offset_opt_resolution;
    private:
};

#endif // OPTIONMENU_H
