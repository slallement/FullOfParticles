#ifndef EFFECTEXPLOSION_H
#define EFFECTEXPLOSION_H

#include "Entity.h"
#include <SFML/System.hpp>
#include <deque>

class ExplosionParticle
{
    protected:
        sf::Sprite sprite;
        float time;
        sf::Vector2f v;

    private:
        float timeAlive;

    public:
        ExplosionParticle(float tAlive);
        void update(float dt);

    friend class EffectExplosion;
};

/* explosion FX */
class EffectExplosion: public Entity
{
    public:
        EffectExplosion();
        EffectExplosion(sf::Vector2f pos, const sf::Texture & text);
        virtual void update(float dt);
        virtual ~EffectExplosion();
        virtual bool isActive() const;

    protected:
        void addParticle();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        static constexpr const float T_ALIVE = 0.10f;//0.15f // time of generation of particle
        static constexpr const float T_GEN_PARTICLE = 0.04f; // particle add rate
        static constexpr const float T_LIVE_PARTICLE = 0.31f;  // time of drawing of a particle
        static constexpr const int NB_PART_RATE = 20; // nb of particle added at each T_GEN_PARTICLE

        bool alive;
        float time;
        float t1;
        float radius;
        std::deque<ExplosionParticle> part;

    private:
};

#endif // EFFECTEXPLOSION_H
