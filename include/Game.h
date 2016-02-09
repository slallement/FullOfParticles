#ifndef GAME_H
#define GAME_H


#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <SFML/Graphics.hpp>
/*
#include "lua.hpp"
#include "lualib.h"
#include "lauxlib.h"
*/
#include "Entity.h"
#include "Behavior.h"
#include "Bullet.h"
#include "GeneratorPreset.h"
#include "BulletModifier.h"
#include "Ship.h"
#include "ShipEnemy.h"
#include "Mission.h"
#include "MissionState.h"
#include "BigImage.h"
#include "PlayerShip.h"
#include "ShipBonus.h"
#include "ShipEvolutive.h"
#include "EffectExplosion.h"

class Mission;

struct ScheduledShip
{
    //ScheduledShip(float t, Ship* s) : time(t),ship(s)) {}
    ScheduledShip() : time(-1),pos(-100.f,-100.f),ship(0) {}
    /** Spawn time */
    float time;
    /** Initial position */
    sf::Vector2f pos;
    /** Ship to spawn */
    ShipEnemy* ship;
    /** Compare ScheduledShip by spawn time */
    static bool comp(const ScheduledShip& s1,const ScheduledShip& s2){
        return s1.time < s2.time;
    }
};

/** Core class of the game, contain the main loop */
class Game
{
    public:
        Game(sf::RenderWindow & window);
        Game(sf::RenderWindow & window, Mission const& mission);
        void init();
        void initMission();
        virtual ~Game();
        bool run();
        void visualize();

        void write();
        void read();
        void initPlayer();
        void addToProgrammation(ShipEnemy const* element, float time);
        void addToProgrammation(unsigned int idelement, float time);
        void addToProgrammation(unsigned int idelement, float time, sf::Vector2f pos);
        unsigned int storeModel(ShipEnemy const& element);
        void addProgrammedInGame(float time);
        void sortProgrammation();

        void manageBonus();
        int getRemainingEnnemyLife() const;
        int getRemainingEnnemyLifeMax() const;
    friend class Mission;

    protected:
        void drawAll();
        void showFailure(sf::Texture screenshot);
        void pauseScreen();
        Generator* setNextVisualisation(int* id, std::vector<float> const& args);
        Generator* setNextVisualisation(int* id);
        void saveVisualisation();
        void setVisuText(sf::Text* text, int pos, std::vector<float> const& args);
        sf::FloatRect getPlayerHitbox();
        void putBonus(Ship& it);
        void manageMission();

        void addAttractor();
        void makePlayer();
        void clear();
        void mainEvent();
        void manageBulletCollision();
        void manageBmodifier();
        void drawEnemies();
        unsigned int getFrameRate();

    // attributes --------------------------------------------------------------

        static const unsigned int FR_LIMIT = 60;
        float dt;

        sf::RenderWindow & window;
        sf::RenderTexture layer_game;
        sf::RenderTexture layer_bullet_enemies;
        sf::Sprite layer_game_s;
        sf::Shader shader_retro;
        sf::Shader shader_blur1;

        std::deque<Bullet> bullet;
        std::deque<Bullet> bulletPlayer;
        std::list<BulletModifier*> bmodifier_enemies;
        std::list<ShipEnemy> enemies;
        std::deque<ShipEnemy> enemiesStored; // adresses are important
        std::deque<ScheduledShip> programmed;
        std::deque<ShipBonus> bonus;
        std::deque<Entity*> decor;

        PlayerShip player;
        bool initialized;
        int nbKill;
        Mission* mission;
        float missionTime;
        int currentMode;
        sf::Clock elapsed;

        sf::Text txt_time;
        BigImage bg;
        sf::Event event;

        sf::Clock elapsed_info;

    private:
};

class GameLearn : public Game
{
    public :
        GameLearn(sf::RenderWindow & w);
        void init();
        void learn();
        void learnInvisible();

    protected:
        void makePlayer();

        static const unsigned int LIFE_SECURITY = 1000;
        static const unsigned int LIFE_INDIVIDUALS = 5;
        static const int NB_INDIVIDUALS = 20;
        ShipEnemy model;
};

#endif // GAME_H
