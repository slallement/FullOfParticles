#include "../include/MissionMenu.h"
#include <iostream>

MissionMenu::MissionMenu(sf::RenderWindow & win):
    Menu(win), game(0), missions()
{
    missions.load();
    offset = option.size();
    makeMenu();
    loadBackground();
}

void MissionMenu::makeMenu()
{
    option.clear();
    option.reserve(missions.size());
    for(unsigned int i=0;i<missions.size();i++){
        std::string s = "Mission "+missions.getMissionName(i)+(missions.getMissionState(i)?"":" (locked) ");
        Button button;
        button.txt = sf::Text(s,*FontManager::getFont("ressources/Symtext.ttf"),32);
        button.f = static_cast<void (Menu::*)()>(&MissionMenu::startMission);
        option.push_back(button);
    }

    option.resize(option.size()+1);
    option.back().txt = sf::Text("Return to main menu",*FontManager::getFont("ressources/Symtext.ttf"),32);
    option.back().f = &Menu::exit;

    initPosition();
}

void MissionMenu::initPosition(){
    Menu::initPosition();
     for(unsigned int i=0;i<missions.size();i++){
        centerTextOnxAxis(option[i].txt,1.f*(i+1)/(missions.size()+2));
    }
    int i = missions.size();
    centerTextOnxAxis(option[i].txt,1.f*(i+1)/(missions.size()+2));
}

void MissionMenu::loadBackground()
{
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

void MissionMenu::update(float)
{
    float vy = cos(elapsed.getElapsedTime().asSeconds()*0.5f);
    float vx = -sin(elapsed.getElapsedTime().asSeconds()*0.25f);
    bg[0].scroll(vx*100.f/60.f);
    bg[0].scrollHor(vy*100.f/60.f);
    bg[1].scroll(vx*45.0f/60.f);
    bg[1].scrollHor(vy*45.0f/60.f);
}

// rewrite the file with the current state
void MissionMenu::updateProgressFile()
{
    makeMenu(); // recreate the menu to take the update
}

// run the game
void MissionMenu::startMission()
{
    if(optionClicked == -1)
        return;
    game = new Game(window);
    if(!game)
        return;

    int idMission = optionClicked-offset;

    // attend to create the mission if its unlocked
    Mission* m = 0;
    m = missions.createMission(idMission,game);

    // if no mission => cancel everything
    if(m==0){
        std::cout<<"Mission"<<(idMission+1)<<std::endl;
        std::cout<<"    non accessible"<<std::endl;
        delete game;
        game = 0;
        end = false;
        return;
    }

    // else => the mission starts
    //end = true; // uncomment if, after a game, we return to the main menu
    bg.clear();

    if(game->run()){
        if(idMission < MissionManager::NB_MISSION){
            if(missions.getMissionState(idMission+1) == false){
                missions.unlock(idMission+1);
                missions.save();
            }
        }else{
            // endscreen
            std::cout<<"Congratulations !"<<std::endl;
        }
    }
    loadBackground();

    // after the end of the mission => we clean the memory
    delete game;
    game = 0;
    optionClicked = -1;
}

MissionMenu::~MissionMenu()
{
    delete game;
}
