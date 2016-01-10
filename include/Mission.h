#ifndef MISSION_H
#define MISSION_H

#include <vector>
#include <list>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Ship.h"
#include "Behavior.h"
#include "GeneratorPreset.h"
#include "Bullet.h"
#include "Utils.h"
#include "Game.h"
#include "BigImage.h"

class MissionState;
class Game;

struct MissionContext
{
    const Game* game;
    std::deque<Bullet>* bullet;
    sf::RenderWindow* window;
    const float* winWidth;
    const float* winHeight;
    sf::RenderTexture* layer_game;
};

class Mission
{
    //friend class Game;
    public:
        Mission(Game* ref);
        virtual ~Mission();
        virtual void init()=0;
        virtual void update(float elapsed);
        bool isContinuing() const{ return unfinished; }
        void abort();
        sf::Image const& getBackground()  {return background;}
        int getMode();
        bool hasFail(){return fail;}
        float getElapsedTime()const{return elapsed;}
        virtual void setState(MissionState* ms);
        unsigned int storeModel(ShipEnemy const& themodel);
        void addToProgrammation(unsigned int id, float time);
        void addToProgrammation(unsigned int id, float time, sf::Vector2f pos);
        void sortProgrammation();
        MissionContext const& getContext() {return context;}
        float getLatencyTime()const{return latencyTime;}
        void end(){unfinished = false;}
    protected:
        static constexpr const float LATENCY = 10.f; // between each mode
        std::vector<int> mode;
        std::vector<sf::Sprite> decor;

        MissionState* missionState; // the current mission state
        MissionContext context;

        Game* game;

        unsigned int currentPart;
        float elapsed;
        float latencyTime;
        bool transition;
        bool unfinished;
        bool fail;

        sf::Image background;
        BigImage* bg;

        TextureManager textures;
        std::vector<MissionState*> allMissionStates;
    private:
};

class Mission1 : public Mission
{
    public:
        Mission1(Game* ref);
        void init();
        void update(float dt);
    protected:
        static constexpr const float begin = 5.f;
        static constexpr const float endduration = 5.f;

        sf::Shader shader;
};

#endif // MISSION_H
