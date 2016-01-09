#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <SFML/Graphics.hpp>
#include <cmath>

class BehaviorAstract
{
    public:
        BehaviorAstract(sf::Vector2f* ref);
        BehaviorAstract(const BehaviorAstract& copy);
        BehaviorAstract(const BehaviorAstract& copy, sf::Vector2f* ref);
        BehaviorAstract& operator=(const BehaviorAstract& copy);
        void linkTo(sf::Vector2f* ref){var = ref;}
        virtual ~BehaviorAstract();

        static float sin200(float t){
            return 200.f*sin(t);
        };
        static float cos200f1(float t){
            return 200.f*cos(t);
        };
        static float cos100f2(float t){
            return 100.f*cos(2*t)+10.f;
        };
        static float inverse(float time)
        {
            //if(time)
            return 100.f*((time > 1.f) ? 1.f : -1.f);
        }
        virtual void update(float dt);
        virtual BehaviorAstract* clone() const {return 0;}
        virtual BehaviorAstract* clone(sf::Vector2f*) const = 0;
    protected:
        sf::Vector2f* var;
        float timeAlive;
    private:
};

class BehaviorNull : public BehaviorAstract
{
    public:
        BehaviorNull() : BehaviorAstract(0){}
        BehaviorNull(sf::Vector2f* ref) : BehaviorAstract(ref){}
        virtual void update(float){}
        virtual BehaviorNull* clone() const { return new BehaviorNull( *this ); }
        virtual BehaviorNull* clone(sf::Vector2f*) const { return new BehaviorNull( *this ); }
};

class BehaviorFunction : public BehaviorAstract
{
    public:
        BehaviorFunction(sf::Vector2f* ref, float (*funx)(float), float (*funy)(float) );
        BehaviorFunction(sf::Vector2f* ref);
        BehaviorFunction(const BehaviorFunction& copy, sf::Vector2f* ref);
        BehaviorFunction& operator=(const BehaviorFunction& copy);
        virtual void update(float );
        void setFx(float (*f)(float));
        void setFy(float (*f)(float));
        virtual BehaviorFunction* clone(sf::Vector2f* ref) const;
    protected:
        float (*fx)(float);
        float (*fy)(float);
};

class BehaviorLinearPath : public BehaviorAstract
{
    public:
        BehaviorLinearPath(sf::Vector2f* ref, std::vector<sf::Vector2f> const& p, float vel, bool timeCste=false);
        BehaviorLinearPath(sf::Vector2f* ref);
        BehaviorLinearPath(const BehaviorLinearPath& copy, sf::Vector2f* ref);
        virtual void update(float dt);
        virtual BehaviorLinearPath* clone(sf::Vector2f* ref) const;
    protected:
        unsigned int current;
        std::vector<sf::Vector2f> points;
        std::vector<float> d;
        float v; // velocity
        bool mode;
};

#endif // BEHAVIOR_H
