#include "../include/Mission.h"
#include "../include/missions/MissionState_1.h"

Mission::Mission(Game* ref) :
    missionState(MissionStateEnd::getState(this)),
    game(ref), currentPart(0), elapsed(0.f), latencyTime(0.f),
    transition(false), unfinished(true), fail(false)
{
    bg = &game->bg;

    context.game = ref;
    context.bullet = &ref->bullet;
    context.window = &ref->window;
    context.winWidth = &ref->window.getDefaultView().getSize().x;
    context.winHeight = &ref->window.getDefaultView().getSize().y;
    context.layer_game = &ref->layer_game;
}

Mission::~Mission()
{
    /*for(unsigned int i=allMissionStates.size(); i!=0; --i)
        delete allMissionStates[i];
    allMissionStates.clear();*/
    missionState->destroy();
    //delete missionState;
}

int Mission::getMode()
{
    return missionState->getMode();
    //return mode[currentPart];
}

void Mission::update(float t)
{
    elapsed += t;
    if(game->programmed.size() <= 0 && game->enemies.size() <= 0){
        latencyTime += t;
        if(latencyTime > LATENCY){
            if(currentPart+1 == mode.size() ){
                //unfinished = false;
            }else if(transition == false){
                latencyTime = 0.f;
                transition = true;
                currentPart++;
                elapsed = 0.f;
            }
        }
    }
    if(transition){
        missionState->nextStep();
        transition = false;
    }
}

void Mission::abort(){
    unfinished = false;
    fail = true;
    /*delete missionState;
    missionState = new MissionStateEnd(this);*/
}

void Mission::setState(MissionState* ms)
{
    delete missionState;
    missionState = ms;
    missionState->init();
}

unsigned int Mission::storeModel(ShipEnemy const& themodel)
{
    return game->storeModel(themodel);
}
void Mission::addToProgrammation(unsigned int id, float time){
    game->addToProgrammation(id, time);
}

void Mission::addToProgrammation(unsigned int id, float time, sf::Vector2f pos){
    game->addToProgrammation(id, time, pos);
}
void Mission::sortProgrammation(){
    game->sortProgrammation();
}

// -----------------------------------------------------------------------------

Mission1::Mission1(Game* ref):
    Mission(ref)
{
    /*mode.push_back(NORMAL);
    mode.push_back(DEATHMATCH);
    mode.push_back(ENDING);*/
}

void Mission1::init()
{
    background.loadFromFile("ressources/img2/bg3.png");

    //--

    MissionState* temp = new MissionStateEnd(this);
    temp = new MissionState1_2(this, temp);
    missionState = new MissionState1_1(this, temp);
    //missionState = new MissionState1_2(this, MissionStateEnd::getState(this));
    missionState->init();
}


void Mission1::update(float dt)
{
    missionState->update();
    bg->scroll(190.f*dt);
    Mission::update(dt);
}
/*
void Mission1::update(float dt)
{
    if(!transition){
        if(currentPart == 0){
            if(elapsed < 5.f){
                if(elapsed < d2+a2 && elapsed > a2){
                    int alpha = 255*(float)((elapsed-a2)/d2);
                    splash2.setColor(sf::Color(255,255,255,alpha));
                }
                if(elapsed < d1+a1 && elapsed > a1){
                    int alpha = 255*(elapsed-a1)/d1;
                    splash1.setColor(sf::Color(255,255,255,alpha));
                }
                layer_game->draw(splash1);
                layer_game->draw(splash2);
            }

            bg->scroll(190.f*dt);
        }
        if(currentPart == 1){
            bg->scroll(10.f*dt);
            if(game->getRemainingEnnemyLife() != 0){
                lifebar.setScale(271.f*game->getRemainingEnnemyLife()/
                                 game->getRemainingEnnemyLifeMax(),1.f);
                layer_game->draw(lifebar);
                layer_game->draw(lifebarBorder);
            }
        }
    }else{
        if(currentPart == 0){
            //init1();
            transition = false;
        }
        if(currentPart == 1){
            init2();
            transition = false;
        }
    }
    if(currentPart == 2){
        if(shader.isAvailable()){
            /layer.clear();
            layer.draw(success,&shader);
            layer.display();
            layer_game->draw(layer);*
            shader.setParameter("texture", sf::Shader::CurrentTexture);
            shader.setParameter("time", latencyTime);
            layer_game->draw(success,&shader);
        }else{
            layer_game->draw(success);
        }
        if(latencyTime > 10.f)
            unfinished = false;
    }
    Mission::update(dt);
}
*/
