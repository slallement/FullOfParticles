#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <SFML/Graphics.hpp>

class ProgressBar : public sf::Drawable
{
    public:
        ProgressBar();
        virtual ~ProgressBar();
        void update(float progress); // progress must be between 0 and 1
        void centerOnX(float winWidth);
    protected:
        const sf::Vector2f offset;
        sf::Texture lifebar_tex1;
        sf::Texture lifebar_tex2;
        sf::Sprite lifebar;
        sf::Sprite lifebarBorder;
        float barSizeMax;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // PROGRESSBAR_H
