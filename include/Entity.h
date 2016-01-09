#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable
{
    public:
        Entity():v(){};
        virtual ~Entity(){};
        virtual void update(float dt)=0;
        virtual bool isActive() const{return true;};
        void setTexture(sf::Texture const& texture, bool originCenterXAxis = false);

        sf::Sprite& getSprite(){return sprite;}
        inline virtual sf::Vector2f getV() const{return v;}
        inline sf::Vector2f getPos() const{return sprite.getPosition();}
        void setV(sf::Vector2f const& nv){v=nv;}
        void setV(float vx, float vy){v.x=vx;v.y=vy;}
        void addV(sf::Vector2f const& nv){v+=nv;}
        void addVx(float val){v.x+=val;}
        void addVy(float val){v.y+=val;}
        void setVx(float x){v.x = x;}
        void setVy(float y){v.y = y;}
    protected:
        sf::Sprite sprite;
        sf::Vector2f v;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(sprite, states);
        }
    private:
};



#endif // ENTITY_H

