#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>

class TextureManagerGlobal
{
    private :
        // The textures that are loaded
        static std::map<std::string, sf::Texture*> textures;

        // Constructor that is not used
        TextureManagerGlobal();
    public:
        // Destructor which deletes the textures previously loaded
        ~TextureManagerGlobal();

        // Loads the texture and returns a pointer to it
        // If it is already loaded, this function just returns it
        // If it cannot find the file, returns NULL
        static sf::Texture *getTexture(std::string str);
        //static sf::IntRect const getTextureRect(string str);
        static sf::IntRect getTextureRectBonus(int str);
        static void assignTextureRect(sf::Sprite & sprite,const std::string name, int id_element);
};

class TextureManager
{
    private :
        // The textures that are loaded
        std::map<std::string, sf::Texture*> textures;

    public:
        TextureManager();
        ~TextureManager();
        void clear();
        sf::Texture* getTexture(std::string str);
        void assignTextureRect(sf::Sprite & sprite,const std::string name, int id_element);
};

class FontManager
{
       static std::map<std::string, sf::Font*> fonts;
       FontManager();
    public:
       ~FontManager();
       static sf::Font *getFont(std::string str);
};

#endif

