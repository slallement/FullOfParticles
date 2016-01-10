#include "../include/MainMenu.h"
#include "../include/MissionMenu.h"

MainMenu::MainMenu(sf::RenderWindow & win):
    Menu(win)
{
    FontManager::getFont("ressources/Symtext.ttf");
    this->loadBackground();

    window.create(sf::VideoMode(Config::WINDOWS_WIDTH, Config::WINDOWS_HEIGHT), "Full of Particles");
    sf::Image icon;
    if(icon.loadFromFile("ressources/icon.png"))
        window.setIcon(256,256,icon.getPixelsPtr());

    sf::Text t = sf::Text("Start Mission",*FontManager::getFont("ressources/Symtext.ttf"),32);

    option.reserve(3);
    option.push_back(Button());
    option.back().txt = t;
    option.back().f = static_cast<void (Menu::*)()>(&MainMenu::runGame);

    t.setString("Options");
    option.push_back(Button());
    option.back().txt = t;
    option.back().f = static_cast<void (Menu::*)()>(&MainMenu::mode);

    #ifdef DEBUG
    option.push_back(Button());
    t.setString("visualize");
    centerTextOnxAxis(t,500.f/800.0f);
    option.back().txt = t;
    option.back().f = static_cast<void (Menu::*)()>(&MainMenu::visualize);

    option.push_back(Button());
    t.setString("learn");
    centerTextOnxAxis(t,700.f/800.0f);
    option.back().txt = t;
    option.back().f = static_cast<void (Menu::*)()>(&MainMenu::learningMode);
    #endif

    t.setString("Exit");
    option.push_back(Button());
    option.back().txt = t;
    option.back().f = static_cast<void (Menu::*)()>(&MainMenu::exit);

    title.setTexture(*TextureManagerGlobal::getTexture("ressources/img/title.png"));
    window.setFramerateLimit(60);
    initPosition();
}

void MainMenu::loadBackground()
{
    if(bg.size()>0)
        return;
    sf::Image bgimg;
    bg.reserve(2);
    if(!bgimg.loadFromFile("ressources/img2/bg5.png")){
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

MainMenu::~MainMenu()
{
    //dtor
}

void MainMenu::initPosition(){
    Menu::initPosition();
    for(unsigned int i=0;i<option.size();++i){
        centerTextOnxAxis(option[i].txt,0.25f+0.75f*(1.f*(1+i)/(1+option.size())));
    }
    float titlescale = 0.4f*window.getDefaultView().getSize().y/title.getTextureRect().height;
    title.setScale(titlescale,titlescale);
    title.setPosition((window.getDefaultView().getSize().x-title.getGlobalBounds().width)/2.f,0.0f);
}

void MainMenu::runGame()
{
    MissionMenu missionMenu(window);
    missionMenu.run();
}

void MainMenu::visualize()
{
    Game* game = new Game(window);
    if(game == NULL)
        return;
    game->visualize();
    delete game;
    game = NULL;
}

void MainMenu::learningMode()
{
    Game* game = new GameLearn(window);
    if(game == NULL)
        return;
    static_cast<GameLearn*>(game)->learn();
    delete game;
    game = NULL;
}

void MainMenu::mode()
{
    OptionMenu optionMenu(window);
    optionMenu.run();
    initPosition();
}

void MainMenu::drawMenu()
{
    window.draw(title);
    Menu::drawMenu();
}

void MainMenu::exit()
{
    end = true;
}

void MainMenu::update(float)
{
    float vy = cos(elapsed.getElapsedTime().asSeconds()*0.5f);
    float vx = -sin(elapsed.getElapsedTime().asSeconds()*0.25f);
    bg[0].scroll(vx*500.f/60.f);
    bg[0].scrollHor(vy*500.f/60.f);
    bg[1].scroll(vx*450.f/60.f);
    bg[1].scrollHor(vy*450.f/60.f);
}
