#ifndef MENU_H
#define MENU_H

#include "Game.h"
#include "BigImage.h"
#include "Utils.h"
#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>

class Menu;
struct Button
{
    Button() : txt(), f(0) {};
    sf::Text txt;
    void (Menu::*f)();
};

/** Generic class for all menus */
class Menu
{
    public:
        Menu(sf::RenderWindow & window);
        /* main loop */
        virtual void run();
        virtual ~Menu();
        virtual void exit();


    protected:
        /* center a text on the X axis, y must be between 0.0f and 1.0f*/
        void centerTextOnxAxis(sf::Text &txt, float y);
        void recenterOptions();
        void recenterOptions(sf::Vector2f oldsize);

        /* (re)position item on screen */
        virtual void initPosition();
        /* load the necessary texture for the background */
        virtual void loadBackground();
        /* update utility function (called at each loop) */
        virtual void update(float time);
        /* draw graphic elements on screen */
        virtual void drawMenu();

        sf::RenderWindow & window;
        sf::Event event;
        /* list of all button on screen */
        std::vector<Button> option;
        /* boolean used to quit the main loop */
        bool end;
        sf::Vector2f clic;
        int optionClicked;
        bool shadersOk;
        sf::RenderTexture render, render2;
        sf::Sprite sprite, sprite2;
        sf::Shader shad_blur;
        int toogle_blur;

        std::vector<BigImage> bg;

    private:
};

#endif // MENU_H

