#include "../include/TextureManager.h"
#include "../include/ShipBonus.h"

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


