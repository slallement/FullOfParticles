#ifndef GENERATORPRESET_H
#define GENERATORPRESET_H

#include "Generator.h"
#include "Utils.h"

class Generator1 : public Generator
{
    public:
        Generator1(std::deque<Bullet>* blist);
        Generator1(std::deque<Bullet>* blist,float rate, int n);
        virtual Generator1* clone() const { return new Generator1( *this ); }
        //void update(float dt);
        void launch();
};

class Generator2 : public Generator
{
    public:
        Generator2(std::deque<Bullet>* blist);
        Generator2(std::deque<Bullet>* blist, float nrate, int nb1, int nb2);
        virtual Generator2* clone() const { return new Generator2( *this ); }
        void launch();
    private:
        float f;
        int n1;
        int n2;
};

class Generator3 : public Generator
{
    public:
        Generator3(std::deque<Bullet>* blist);
        Generator3(std::deque<Bullet>* blist, float nrate, int nb1, int nb2);
        Generator3(std::deque<Bullet>* blist,
                   float nrate, int nbbranch, int nbshotperwave,
                   float ratesin, float amplitudesin);
        virtual Generator3* clone() const { return new Generator3( *this ); }
        void launch();
    private:
        float f;
        int n1;
        int n2; // number of bullet "aligned"
        float wsin;
        float ampsin;
};

class Generator4 : public Generator
{
    public:
        Generator4(std::deque<Bullet>* blist);
        Generator4(std::deque<Bullet>* blist, float nt1, int nb1, int nb2);
        Generator4(std::deque<Bullet>* blist,
                   float nrate, int nbpetalsMin, int nbpetalsMax, int nbrepetition, float noffset);
        virtual Generator4* clone() const { return new Generator4( *this ); }
        void launch();
    private:
        float f;
        int n1;
        int n2;
        int n3;
        float offset;
};

class Generator5 : public Generator
{
    public:
        Generator5(std::deque<Bullet>* blist);
        Generator5(std::deque<Bullet>* blist,
            float n_rate, float n_nbbranch, float n_ampcard, float n_ratecard,
            float n_radius_card, float n_raterotbranch, float n_offset);
        virtual Generator5* clone() const { return new Generator5( *this ); }
        void launch();
    private:
        float r1;
        int count;
        float amplitudecyclo;
        float ratecyclo;
        float radiuscyclo;
        float raterotbranch;
        float offset;
};

class Generator6 : public Generator
{
    public:
        Generator6(std::deque<Bullet>* blist);
        float f(float x, float fact);
        virtual Generator6* clone() const { return new Generator6( *this ); }
        void launch();
        float k;
        float a;
        float b;
        float vmin;
        float vmax;
        float rotation;
        float period;
        int mode;
    protected:
        void computePeriod();
};

class Generator7 : public Generator
{
    public:
        Generator7(std::deque<Bullet>* blist);
        Generator7(std::deque<Bullet>* blist,float rate, int n);
        virtual Generator7* clone() const { return new Generator7( *this ); }
        void launch();
    protected:
        float a,b;
};

class Generator8 : public Generator
{
    public:
        Generator8 (std::deque<Bullet>* blist);
        Generator8 (std::deque<Bullet>* blist,float rate, int n);
        virtual Generator8 * clone() const { return new Generator8 ( *this ); }
        void launch();
    protected:
        float a,b;
};

class Generator9 : public Generator
{
    public:
        Generator9 (std::deque<Bullet>* blist);
        Generator9 (std::deque<Bullet>* blist,float rate, int n);
        virtual Generator9 * clone() const { return new Generator9 ( *this ); }
        void launch();
    protected:
        float a,b;
};

class Generator10 : public Generator
{
    public:
        Generator10 (std::deque<Bullet>* blist);
        Generator10 (std::deque<Bullet>* blist,float rate, int n);
        virtual Generator10 * clone() const { return new Generator10 ( *this ); }
        void launch();
    protected:
        float a,b;
};

// ---

class Generator1p : public PlayerGenerator
{
    public:
        Generator1p(std::deque<Bullet>* blist);
        Generator1p(std::deque<Bullet>* blist,float rate, int n);
        virtual Generator1p* clone() const { return new Generator1p( *this ); }
        //void update(float dt);
        void launch();
        void improve(int mode,int factor=1);
};

class Generator2p : public PlayerGenerator
{
    public:
        Generator2p(std::deque<Bullet>* blist);
        Generator2p(std::deque<Bullet>* blist,float rate, int n, float radiusMinimum = 20.f);
        virtual Generator2p* clone() const { return new Generator2p( *this ); }
        //void update(float dt);
        void launch();
        void improve(int mode,int factor=1);
    protected:
        int count;
        static const float minRate;
        float radiusMin;
};

#endif // GENERATORPRESET_H
