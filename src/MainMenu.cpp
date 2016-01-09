#include "../include/MainMenu.h"
#include "../include/MissionMenu.h"

MainMenu::MainMenu(sf::RenderWindow & win):
    Menu(win), missionMenu(win)
{
    FontManager::getFont("ressources/Symtext.ttf");
    this->loadBackground();

    window.create(sf::VideoMode(Utils::WINDOWS_WIDTH, Utils::WINDOWS_HEIGHT), "Dodger King");
    sf::Image icon;
    if(icon.loadFromFile("ressources/icon.png"))
        window.setIcon(256,256,icon.getPixelsPtr());

    sf::Text t = sf::Text("Start Mission",*FontManager::getFont("ressources/Symtext.ttf"),32);
    centerTextOnxAxis(t,300.f);

    option.resize(3);
    option[0].txt = t;
    option[0].f = static_cast<void (Menu::*)()>(&MainMenu::runGame);

    t.setString("Exit");
    centerTextOnxAxis(t,600.f);
    option[1].txt = t;
    option[1].f = static_cast<void (Menu::*)()>(&MainMenu::exit);

    option[2].txt = t;
    option[2].txt.setString("Mode : windowed");
    centerTextOnxAxis(option[2].txt,400.f);
    option[2].f = static_cast<void (Menu::*)()>(&MainMenu::mode);

    #ifdef DEBUG
    option.push_back(Button());
    t.setString("visualize");
    centerTextOnxAxis(t,500.f);
    option.back().txt = t;
    option.back().f = static_cast<void (Menu::*)()>(&MainMenu::visualize);

    option.push_back(Button());
    t.setString("learn");
    centerTextOnxAxis(t,700.f);
    option.back().txt = t;
    option.back().f = static_cast<void (Menu::*)()>(&MainMenu::learningMode);
    #endif

    title.setTexture(*TextureManagerGlobal::getTexture("ressources/img/title.png"));
    title.setPosition((window.getDefaultView().getSize().x-title.getGlobalBounds().width)/2.f,title.getPosition().y);
    window.setFramerateLimit(60);
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

void MainMenu::runGame()
{
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

void MainMenu::initPosition(){
    Menu::initPosition();
    recenterOptions();
    title.setPosition((window.getDefaultView().getSize().x-title.getGlobalBounds().width)/2.f,title.getPosition().y);

    //render.create(window.getSize().x,window.getSize().y);
    //render2.create(window.getSize().x,window.getSize().y);
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
