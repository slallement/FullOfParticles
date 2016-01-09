#include "../include/MissionState.h"

MissionState::MissionState(Mission* m, MissionState* ms):
    mission(m), nextMs(ms), mode(UNKNOWN)
{
    if(mission)
        context = &(mission->getContext());
    else
        context = 0;
}

MissionState::~MissionState()
{
    //dtor
}

void MissionState::destroy()
{
    if(nextMs)
        nextMs->destroy();
    delete this;
}

void MissionState::init(){}

void MissionState::update(float){}

void MissionState::nextStep()
{
    mission->setState(nextMs);
}

// -----------------------------------------------------------------------------

MissionStateEnd* MissionStateEnd::ms(0);

MissionStateEnd::MissionStateEnd(Mission* m) :
    MissionState(m,0)
{
    mode = ENDING;
}

void MissionStateEnd::nextStep()
{
    mission->end();
}

void MissionStateEnd::update(float)
{
    float latencyTime = mission->getLatencyTime();
    if(shader.isAvailable()){
        shader.setParameter("texture", sf::Shader::CurrentTexture);
        shader.setParameter("time", latencyTime);
        mission->getContext().layer_game->draw(success,&shader);
    }else{
        mission->getContext().layer_game->draw(success);
    }
    /*if(latencyTime > 10.f){
        mission->end();
    }*/

}

void MissionStateEnd::init()
{
    if (sf::Shader::isAvailable())
    {
        //if (layer.create(window->getSize().x,window->getSize().y)){
            if (!shader.loadFromFile("shaders/sinwave.vert", "shaders/sinwave.frag"))
            {
                // error...
            }
        //}
    }
    success_tex.loadFromFile("ressources/img2/m1success.png");
    success.setTexture(success_tex);
    success.setTextureRect(sf::IntRect(0,0,
                        success.getGlobalBounds().width+10,
                        success.getGlobalBounds().height*2));
    success.setPosition((*context->winWidth-success.getGlobalBounds().width)/2,
                        (*context->winHeight-success.getGlobalBounds().height)/2);
    success_tex.setSmooth(true);
}

MissionStateEnd* MissionStateEnd::getState(Mission* m)
{
    if(!ms){
        ms = new MissionStateEnd(m);
    }
    return ms;
}


