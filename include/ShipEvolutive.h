#ifndef SHIPEVOLUTIVE_H
#define SHIPEVOLUTIVE_H

#include "Ship.h"
#include <vector>
#include <string>
#include <fstream>
#include <stdint.h>
#include <SFML/Graphics.hpp>

#define SHIPEVOLUTIVE_SIZE 3

struct gene{
    int16_t f;
    float time;
    float strength;
    int16_t next;
};

class ShipEvolutive : public Ship
{
    public:
        ShipEvolutive(Ship* ref,std::string n="");
        ShipEvolutive(ShipEvolutive& ref, gene* genome);
        virtual ~ShipEvolutive();
        void update(float dt);
        void reset();
        static float reproduction(std::vector<ShipEvolutive> & evo);
        std::string getName() const{return name;}
        float getTime() const {return time;}
        float getFitness() const {
            return (time + 0.5f*timebul);
        }
        int getGeneration() const{return generation;}
        static bool comp(const ShipEvolutive& s1,const ShipEvolutive& s2){
            return s1.getFitness()>s2.getFitness();
        }

        void mutation(int probabilty=1);
        void act(int f, float s);

        static const int nbgene = SHIPEVOLUTIVE_SIZE*SHIPEVOLUTIVE_SIZE;
        struct Crossed{
            gene a[nbgene];
            gene b[nbgene];
        };
        void writeGenome();
        //void setPosPlayer(sf::Vector2f const& pos){posPlayer = pos;}
        void setBulletPlayer(std::deque<Bullet>* bul){bulletPlayer = bul;}
    protected:
        void writeGenome(std::string path);
        void readGenome(std::string path);

        void goFurther1(float strenght);
        void goFurther2(float strenght, int no);
        void goFurther3(float strenght, int no, int part);
        void randomiseGene(int i);
        void randomiseGeneSoft(int i);
        void initRandom();
        void expression(gene g);
        static Crossed crossover(ShipEvolutive& s1, ShipEvolutive& s2);

        Ship* body;
        std::string name;
        static const int nbact = 18;
        static const int probmutation = 5;
        static const int probcross = 30;
        gene chrom[nbgene];
        float time;
        float timebul;
        float t1;
        int16_t generation;
        int currentGene;

        //sf::Vector2f posPlayer;
        std::deque<Bullet>* bulletPlayer;
    private:
};

#endif // SHIPEVOLUTIVE_H
