#include "include/MainMenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Utils.h"
#include "include/Config.h"

int main()
{
    srand (time(NULL));

    sf::Sprite title(*TextureManagerGlobal::getTexture("ressources/img/title.png")); // splash screen

    sf::RenderWindow window(sf::VideoMode(title.getTextureRect().width,title.getTextureRect().height), Config::TITLE_WINDOW, sf::Style::None);
    window.draw(title);
    window.display();
    //sf::RenderWindow window(sf::VideoMode(1600, 900), "Dodger King",sf::Style::Fullscreen);

    MainMenu menu(window);
    menu.run();
    return 0;
}
