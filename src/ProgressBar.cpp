#include "../include/ProgressBar.h"

ProgressBar::ProgressBar():
    offset(12.f,12.f)
{
    // life bar
    lifebar_tex1.loadFromFile("ressources/img2/lifebar.png");
    lifebar_tex2.loadFromFile("ressources/img2/lifebargrad.png");
    lifebar_tex2.setRepeated(true);
    lifebarBorder.setTexture(lifebar_tex1);
    lifebar.setTexture(lifebar_tex2);
    barSizeMax = lifebarBorder.getGlobalBounds().width-offset.x*2;
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::centerOnX(float winWidth)
{
    const int posx = (winWidth-lifebarBorder.getGlobalBounds().width)/2;
    const int posy = 10.f;
    lifebarBorder.setPosition(posx,posy);
    lifebar.setPosition(posx,posy);
    lifebar.move(offset); // offset between the bar from the border
}

void ProgressBar::update(float progress)
{
    lifebar.setScale(barSizeMax*progress,1.f);
}

void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(lifebar, states);
    target.draw(lifebarBorder, states);
}
