#include "../include/Utils.h"
#include <cmath>
#include <iostream>

// ---


float Utils::cosineInterpolate(float y1, float y2, float x)
{
   float mu2 = (1.f-cos(x*PI))/2.f;
   return(y1*(1.f-mu2)+y2*mu2);
}

std::vector<sf::Vector2f> Utils::getInterpolationCosine(std::vector<sf::Vector2f> const& path, unsigned int subdivision)
{
    std::vector<sf::Vector2f> res((path.size()-1)*subdivision+1);
    for(unsigned int i=0;i<path.size()-1;i++){
        for(unsigned int j=0;j<subdivision;j++){
            //res[i+j].y = path[i].y+cosineInterpolate(path[i].y,path[i+1].y,1.f/j);
            unsigned int id = i*subdivision+j;
            float part = (float)j/(subdivision);
            res[id].y = path[i].y+part*(path[i+1].y-path[i].y);
            res[id].x = cosineInterpolate(path[i].x,path[i+1].x,part);
        }
    }
    res[(path.size()-1)*subdivision] = path[path.size()-1];
    return res;
}

std::vector<sf::Vector2f> Utils::getPathFractionned(std::vector<sf::Vector2f> const& path)
{
    std::vector<sf::Vector2f> res(path.size());
    res[0] = path[0];
    for(unsigned int i=1;i<path.size();i++)
    {
        res[i] = path[i]-path[i-1];
    }
    return res;
}

float id(float x){
    return x;
}


