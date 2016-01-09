#ifndef MENU_H
#define MENU_H

#include "Game.h"
#include "BigImage.h"
#include "Utils.h"
#include <vector>
#include <list>
#include <algorithm>
#include <SFML/Graphics.hpp>

class Menu;
struct Button
{
    Button() : txt(),f(0) {};
    sf::Text txt;
    void (Menu::*f)();
};

class Menu
{
    public:
        Menu(sf::RenderWindow & window);
        virtual void run();
        virtual ~Menu();
        virtual void exit();

    protected:
        void centerTextOnxAxis(sf::Text &txt, float y);
        void recenterOptions();

        virtual void initPosition();
        virtual void loadBackground();
        virtual void update(float time);
        virtual void drawMenu();

        sf::RenderWindow & window;

        sf::Event event;
        std::vector<Button> option;
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

