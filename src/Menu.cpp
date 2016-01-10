#include "../include/Menu.h"

Menu::Menu(sf::RenderWindow & win):
    window(win), event(), option(),
    end(false), clic(), optionClicked(-1), bg()
{

}

void Menu::loadBackground()
{
    if(!window.isOpen())
        return;

    if(bg.size()>0)
        return;
    sf::Image bgimg;
    bg.reserve(2);
    if(!bgimg.loadFromFile("ressources/img2/bg2.png")){
        //erreur
    }else{
        bg.push_back(BigImage(bgimg));
    }
    if(!bgimg.loadFromFile("ressources/img2/bgnoise1.png")){
        //erreur
    }else{
        bg.push_back(BigImage(bgimg));
    }
}

Menu::~Menu()
{
    //dtor
}

void Menu::centerTextOnxAxis(sf::Text &txt, float y)
{
    txt.setPosition((window.getDefaultView().getSize().x-txt.getGlobalBounds().width)/2.f,
        window.getDefaultView().getSize().y*y);
}

void Menu::recenterOptions()
{
    for(unsigned int i=0;i<option.size();++i){
         centerTextOnxAxis(option[i].txt, option[i].txt.getPosition().y/window.getDefaultView().getSize().y);
    }
}

void Menu::recenterOptions(sf::Vector2f oldsize)
{
    for(unsigned int i=0;i<option.size();++i){
         centerTextOnxAxis(option[i].txt, option[i].txt.getPosition().y/oldsize.y);
    }
}

void Menu::initPosition()
{
    render.create(window.getDefaultView().getSize().x,window.getDefaultView().getSize().y);
    render2.create(window.getDefaultView().getSize().x,window.getDefaultView().getSize().y);
}

void Menu::run()
{
    initPosition();
    sprite.setTexture(render.getTexture());
    sprite2.setTexture(render2.getTexture());

    shadersOk = true;
    if(!shad_blur.loadFromFile("shaders/gblur.vert", "shaders/gblur.frag")){
        shadersOk = false;
    }else{
        shad_blur.setParameter("texture_size", 0.8f*sf::Vector2f(render.getSize())); // 0.8 -> inverse size of blur
    }
    toogle_blur = 0;

    sf::Clock elapsed;
    sf::Clock clock;
    float dt;
    end = false;
    while (window.isOpen() && !end)
    {
        dt = clock.restart().asSeconds();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape){
                    end = true;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    clic = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                }
            }else if(event.type == sf::Event::MouseButtonReleased) {
                for(unsigned int i=0; i<option.size();++i){
                    if(option[i].txt.getGlobalBounds().contains(
                            window.mapPixelToCoords(
                            (sf::Mouse::getPosition(window))) )
                    && option[i].txt.getGlobalBounds().contains(
                           clic) )
                    {
                        if(option[i].f != NULL){
                            //bg.clear();
                            optionClicked = i;
                            (this->*option[i].f)();
                            /*if(end==false)
                                loadBackground();*/
                        }
                    }
                }
            }

        }

        if(end == true){
            break;
        }
        update(dt);

        window.clear();
        for(unsigned int i=0;i<bg.size();++i)
            window.draw(bg[i]);
        drawMenu();
        window.display();
    }
}

void Menu::exit(){
    end = true;
}

void Menu::drawMenu()
{
    if(shadersOk){
        render.clear(sf::Color::Transparent);
    }
    for(unsigned int i=0; i<option.size();++i){
        if(option[i].txt.getGlobalBounds().contains(
                    window.mapPixelToCoords(
                    (sf::Mouse::getPosition(window)))) )
        {
            option[i].txt.setColor(sf::Color(200,200,255,200));
        }else{
            option[i].txt.setColor(sf::Color(255,255,255,255));
        }
        if(shadersOk)
            render.draw(option[i].txt);
        else
            window.draw(option[i].txt);
    }
    if(shadersOk){
        render.display();
        // render 2

        sprite.setColor(sf::Color::Black);
        render2.clear(sf::Color::Transparent);
        //shad_blur.setParameter("horizontal",toogle_blur^=1);
        render2.draw(sprite,&shad_blur);
        render2.display();
        toogle_blur^=1;
        shad_blur.setParameter("horizontal",toogle_blur);

        window.draw(sprite2,&shad_blur);
        sprite.setColor(sf::Color::White);
        window.draw(sprite);
    }
}

void Menu::update(float)
{
}
