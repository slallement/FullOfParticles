#include "../include/Utils.h"
#include <cmath>
#include <iostream>
// ---
unsigned int Utils::WINDOWS_WIDTH  = 1600;
unsigned int Utils::WINDOWS_HEIGHT = 900;

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

#include "../include/ShipBonus.h"

float id(float x){return x;}

TextureManagerGlobal::TextureManagerGlobal(){}

std::map<std::string, sf::Texture*> TextureManagerGlobal::textures;

sf::Texture* TextureManagerGlobal::getTexture(std::string str)
{

   // See if we have already loaded this texture
   if(textures.find(str) != textures.end())
      return textures[str];

   // Haven't loaded it yet, time to create it
   sf::Texture *texture = new sf::Texture();
   if(texture->loadFromFile(str))
   {
      textures[str] = texture;
      return textures[str];
   }
   else
   {
      // Could not load the file
      delete texture;
      return NULL;
   }

}

TextureManagerGlobal::~TextureManagerGlobal()
{
   // Delete all of the textures we used
   sf::Texture *texture;
   std::map<std::string, sf::Texture*>::iterator iter = textures.begin();
   while(iter != textures.end())
   {
      texture = iter->second;
      delete texture;
      iter++;
   }
}



/*sf::IntRect const TextureManagerGlobal::getTextureRect(string str)
{
    if(str == "bonus+life1"){
        return sf::IntRect(0,0,20,20);
    }else if(str == "bonus+shield1"){
        return sf::IntRect(20,0,20,20);
    }
    // unfounded
    return sf::IntRect(0,0,0,0);
}*/

sf::IntRect TextureManagerGlobal::getTextureRectBonus(int s)
{
    if(s == ShipBonus::LIFE_LV1){
        return sf::IntRect(40,0,20,20);
    }else if(s == ShipBonus::SHILED_LV1){
        return sf::IntRect(20,0,20,20);
    }else if(s == ShipBonus::IMPROVE_RATE1){
        return sf::IntRect(20,20,20,20);
    }
    // unfounded
    return sf::IntRect(0,0,20,20);
}

void TextureManagerGlobal::assignTextureRect(sf::Sprite & sprite, const std::string name, int e){
    sprite.setTexture(*TextureManagerGlobal::getTexture(name));
    if(name == "ressources/img/bullets1.png"){
        if(e == 1){
            sprite.setTextureRect(sf::IntRect(0,0,12,20));
        }else if(e == 2){
            sprite.setTextureRect(sf::IntRect(12,0,12,21));
        }else if(e == 3){
            sprite.setTextureRect(sf::IntRect(24,0,12,24));
        }else if(e == 4){
            // b4 size 10x10
            sprite.setTextureRect(sf::IntRect(0,20,10,10));
        }else if(e == 5){
            sprite.setTextureRect(sf::IntRect(36,0,20,20));
        }else if(e == 6){
            sprite.setTextureRect(sf::IntRect(56,0,40,40));
        }else if(e == 7){
            sprite.setTextureRect(sf::IntRect(96,0,20,27));
        }
    }
}

// ---

TextureManager::TextureManager():
    textures()
{}

sf::Texture* TextureManager::getTexture(std::string str)
{

   // See if we have already loaded this texture
   if(textures.find(str) != textures.end())
      return textures[str];

   // Haven't loaded it yet, time to create it
   sf::Texture *texture = new sf::Texture();
   if(texture->loadFromFile(str))
   {
      textures[str] = texture;
      return textures[str];
   }
   else
   {
      // Could not load the file
      delete texture;
      return NULL;
   }

}

TextureManager::~TextureManager()
{
   // Delete all of the textures we used
   sf::Texture *texture;
   std::map<std::string, sf::Texture*>::iterator iter = textures.begin();
   while(iter != textures.end())
   {
      texture = iter->second;
      delete texture;
      iter++;
   }
}

// font manager ---

FontManager::FontManager(){}

std::map<std::string, sf::Font*> FontManager::fonts;

sf::Font* FontManager::getFont(std::string str)
{
    if(fonts.find(str) != fonts.end())
        return fonts[str];
    sf::Font *font = new sf::Font();
    if(font->loadFromFile(str)){
      fonts[str] = font;
      return fonts[str];
   }else{
      delete font;
      return NULL;
   }

}

FontManager::~FontManager()
{
   sf::Font *font;
   std::map<std::string, sf::Font*>::iterator iter = fonts.begin();
   while(iter != fonts.end())
   {
      font = iter->second;
      delete font;
      iter++;
   }

}



