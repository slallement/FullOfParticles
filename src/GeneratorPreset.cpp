#include "../include/GeneratorPreset.h"
#include "../include/Generator.h"

int Generator::nbArg [] = {2,3,5,5,7};

/** Generator 1 */

Generator1::Generator1(std::deque<Bullet>* blist):
    Generator(blist)
{
    n = 1;
    rate = 0.3f;
}

Generator1::Generator1(std::deque<Bullet>* blist, float nrate, int nb):
    Generator(blist)
{
    n = nb;
    rate = nrate;
}

void Generator1::launch()
{

    /*if(static_cast<int>(t2)%20 >= 10){
        n = 9;
    }*/
    for(int i=0; i<n; i++) {
        float theta = PI*(i+1)/(float)(n+1)+sprite.getRotation()/RAD_TO_DEG;
        float r = 40.f;
        sf::Vector2f pos( cos(theta),  sin(theta));

        bullet->push_back(Bullet());
        TextureManagerGlobal::assignTextureRect(bullet->back().getSprite(),"ressources/img/bullets1.png",1);
        bullet->back().getSprite().setColor(sf::Color(255,200,100));
        bullet->back().getSprite().setOrigin(sf::Vector2f(bullet->back().getSprite().getLocalBounds().width/2.f,0.f));
        bullet->back().getSprite().setPosition(sprite.getPosition());
        bullet->back().getSprite().move(
            sf::Vector2f(sprite.getLocalBounds().width,sprite.getLocalBounds().height)/-2.f);
        bullet->back().getSprite().move(r*pos);
        bullet->back().getSprite().setRotation((-HALF_PI+theta)*RAD_TO_DEG);
        bullet->back().setV(pos*500.f);
    }

}

/** generator 2
circular, aquatic style
n1 number of branches
n2 number of bubbles*/

Generator2::Generator2(std::deque<Bullet>* blist):
    Generator(blist), f(1)
{
    rate = 0.3f;
    n1 = 3;
    n2 = 15;
    n = n1;
}

Generator2::Generator2(std::deque<Bullet>* blist, float nrate, int nb1, int nb2):
    Generator(blist), f(1)
{
    rate = nrate;
    n1 = nb1;
    n2 = nb2;
    n = n1;
}

void Generator2::launch()
{
    // order : A A 0 B B 0
    // where 0 = nothing
    if(nblaunch%3 == 2) {
        f *= -1;
        return;
    }
    if(nblaunch%6 <= 2) {
        // phase A
        n = n1;
    } else {
        // phase B
        n = n2;
    }
    for(int j=0; j<2; j++) {
        for(int i=0; i<n; ++i) {
            float theta = i * GOLDEN_ANGLE+f*nblaunch*0.1f;

            float r = 25.f*(1.f+sqrt(i/((float)n)) );
            sf::Vector2f pos(cos(theta),  sin(theta));

            bullet->push_back(Bullet());
            if(f<0) {
                TextureManagerGlobal::assignTextureRect(bullet->back().getSprite(),"ressources/img/bullets1.png",4);//size10
                bullet->back().getSprite().setColor(sf::Color(50,150,250));
            } else {
                TextureManagerGlobal::assignTextureRect(bullet->back().getSprite(),"ressources/img/bullets1.png",6);//size40
                bullet->back().getSprite().setColor(sf::Color(200,255,255));
            }
            bullet->back().getSprite().setOrigin(sf::Vector2f(bullet->back().getSprite().getLocalBounds().width/2.f,0.f));
            bullet->back().getSprite().setPosition(sprite.getPosition());
            bullet->back().getSprite().move(
                sf::Vector2f(sprite.getLocalBounds().width,sprite.getLocalBounds().height)/-2.f);
            bullet->back().getSprite().move(r*pos);
            bullet->back().getSprite().setRotation((-HALF_PI+theta)*RAD_TO_DEG);
            float bulv = 100.f +  ((f>0.f)?50.f:0.f) + ((j>0)?100.f:0.f);
            //std::cout<<"vit"<<bulv<<std::endl;
            bullet->back().setV(pos*bulv);
        }
    }
}

/** Generator 3 */

Generator3::Generator3(std::deque<Bullet>* blist):
    Generator(blist)
{
    rate = 0.11f;
    n1 = 10;
    n2 = 10;
    n = n1;
    wsin = 0.1f;
    ampsin = 0.2f;
}

Generator3::Generator3(std::deque<Bullet>* blist, float nrate, int nbbranch, int nbshotperwave, float ratesin, float amplitudesin):
    Generator(blist)
{
    rate = nrate;
    n1 = nbbranch;
    n2 = nbshotperwave;
    if(n2==0)
        n2 = 1;
    n = n1;
    wsin = ratesin;
    ampsin = amplitudesin;
}

void Generator3::launch()
{
    if(n==0) {
        if((nblaunch)%(2*n2) == 0) {
            n=n1;
        } else {
            return;
        }
    }
    float sinoffset = sin(nblaunch*wsin)*ampsin;
    for(int i=0; i<n; ++i) {
        float theta = TWO_PI*i/n+sinoffset+HALF_PI;

        float r = 1.f;
        sf::Vector2f pos(cos(theta), sin(theta));

        bullet->push_back(Bullet());

        //TextureManager::assignTextureRect(bullet->back().getSprite(),"ressources/img/bullets1.png",2);
        setStandardBullet("ressources/img/bullets1.png",2);
        bullet->back().getSprite().setRotation((-HALF_PI+theta)*RAD_TO_DEG);

        bullet->back().getSprite().move(r*pos);
        float bulv = 400.f;
        //std::cout<<"vit"<<bulv<<std::endl;
        bullet->back().setV(pos*bulv);
    }
    if(nblaunch%(2*n2) == n2-1) {
        for(int i=0; i<n; ++i) {
            float theta = TWO_PI*(i+0.5f)/n+sinoffset+HALF_PI;

            float r = 1.f;
            sf::Vector2f pos(cos(theta), sin(theta));

            bullet->push_back(Bullet());

            //setStandardBullet("ressources/img/b5.png");
            setStandardBullet("ressources/img/bullets1.png",7);
            bullet->back().getSprite().move(r*pos);
            bullet->back().getSprite().setRotation((-HALF_PI+theta)*RAD_TO_DEG);
            float bulv = 350.f;
            //std::cout<<"vit"<<bulv<<std::endl;
            bullet->back().setV(pos*bulv);
        }
        n = 0;
    }
}

/** Generator 4
a rose like generator
n1 number of petals min
n2 number of petals max
offset : angular offset

default:

Generator4(bullet, 0.55f, 3, 7, 3, 0.f) */



Generator4::Generator4(std::deque<Bullet>* blist):
    Generator(blist)
{
    rate = 0.55f;
    n1 = 3;
    n2 = 5;//7-3+1;
    n3 = 3;
    offset = 30.f*DEG_TO_RAD;

    n2 = n2-n1+1;
    n = 25*n1;
}

Generator4::Generator4(std::deque<Bullet>* blist,
                       float nrate, int nbpetalsMin, int nbpetalsMax, int nbrepetition, float noffset):
    Generator(blist)
{
    rate = nrate;
    n1 = nbpetalsMin;
    n2 = nbpetalsMax-nbpetalsMin+1;
    n3 = nbrepetition;
    n = 25*n1;
    offset = noffset*DEG_TO_RAD;
}

void Generator4::launch()
{
    float tn = 25*(n1+nblaunch/(n3*2)%n2);
    if((nblaunch%(n3*2))< n3)
        return;

        for(int i=0; i<tn; ++i) {
            float theta = i*TWO_PI/(tn+n1-1)+offset;
            float theta2 = theta+PI-i*0.25f * n1*25.f/n;

            float r = 20.f;
            sf::Vector2f pos(cos(theta), sin(theta));
            sf::Vector2f pos2(cos(theta2), sin(theta2));

            bullet->push_back(Bullet());

            //bullet->back().getSprite().setTexture(*TextureManager::getTexture("ressources/img/b3.png"));
            setStandardBullet("ressources/img/bullets1.png",3);
            bullet->back().getSprite().setColor(sf::Color(235,100,255));

            /*bullet->back().getSprite().setOrigin(sf::Vector2f(bullet->back().getSprite().getLocalBounds().width/2.f,0.f));
            bullet->back().getSprite().setPosition(sprite.getPosition());*/
            bullet->back().getSprite().move(
                sf::Vector2f(sprite.getLocalBounds().width,sprite.getLocalBounds().height)/-2.f);
            bullet->back().getSprite().move(r*pos);
            bullet->back().getSprite().setRotation((-HALF_PI+theta)*RAD_TO_DEG);
            float bulv = 200.f;
            //std::cout<<"vit"<<bulv<<std::endl;
            bullet->back().setV(pos2*bulv);
        }

}

/** Generator 5
Cycloid like **/

Generator5::Generator5(std::deque<Bullet>* blist):
    Generator(blist), count(0)
{
    //r1 = 0.09f;
    r1 = 0.01f;
    n = 5;
    amplitudecyclo = 5.f;
    ratecyclo = 0.02f;
    radiuscyclo = 100.f;
    raterotbranch = 0.1f;
    offset = 0.f;

    rate = 0.01f;
}

/** default :
0.09f, 3.f, 5.f, 0.02f, 100.f, 0.1f, 0.f
*/
Generator5::Generator5(std::deque<Bullet>* blist,
            float n_rate, float n_nbbranch, float n_ampcard, float n_ratecard,
            float n_radius_card, float n_raterotbranch, float n_offset):
    Generator(blist), count(0)
{
    r1 = n_rate;

    n = (int)n_nbbranch;
    offset = n_offset;
    amplitudecyclo = n_ampcard;
    ratecyclo = n_ratecard;
    radiuscyclo = n_radius_card;
    raterotbranch = n_raterotbranch;

    rate = 0.01f;
}

void Generator5::launch()
{
    count++;
    if(count == 50){
        rate = 0.01f;
    }else
    if(count>75*3){
        count = 0;
        rate = r1;
    }

    float r2 = radiuscyclo*(1.f+sin(TWO_PI*0.1f*nblaunch*rate))/2.f;
    float temp = TWO_PI*nblaunch*rate*sin(ratecyclo*nblaunch*rate)*amplitudecyclo;
    for(int i=0; i<n; ++i) {
        float theta2 = TWO_PI*i/n+offset+TWO_PI*nblaunch*rate*raterotbranch;
        float theta3 = theta2+temp;
        //float theta3 = TWO_PI*i/n+temp;
        float r = 20.f;//*sin(nblaunch*rate+HALF_PI*i*n);
        //sf::Vector2f pos(cos(theta), sin(theta));
        sf::Vector2f pos2(cos(theta2), sin(theta2));
        sf::Vector2f pos3(cos(theta3), sin(theta3));

        bullet->push_back(Bullet());

            setStandardBullet("ressources/img/b4+t10.png");
            bullet->back().getSprite().setColor(sf::Color(235,200,255));
        bullet->back().getSprite().setRotation((theta3-HALF_PI)*RAD_TO_DEG);
        bullet->back().getSprite().move(r*pos2);
        bullet->back().getSprite().move(r2*pos3);

        float bulv = 300.f;
        //std::cout<<"vit"<<bulv<<std::endl;
        bullet->back().setV(pos2*bulv);
    }

}

/** Generator6 */

Generator6::Generator6(std::deque<Bullet>* blist):
    Generator(blist)
{
    rate = 1.f;
    n = 150.f;
    a = 1.f;
    b = 6.f;
    vmin = 100.f;
    rotation = 0.2f*1.f/n;
    mode = 10;
    computePeriod();
}

void Generator6::computePeriod()
{
    k = a/b;
    period = b;
    if((int)a%2==0) period *= 2.f;
    if( (int)b%2==0) period *= 2.f;
    //if((int)a%2==0 && (int)b%2==0)period = 4.f;
}

void Generator6::launch()
{
    float dec = rotation*nblaunch*rate*TWO_PI;
    if(mode > 0){
        a = nblaunch%mode+1;
        b = mode-a+1;
        computePeriod();
    }
    for(int i=0; i<n; ++i) {
        //while(i%15>5) i++;
        float theta = PI*(i+1)/n*period;
        float theta2 = theta +dec;
        sf::Vector2f pos(cos(theta2), sin(theta2));

        float bulv = 200.f*(cos(k*theta));
        bulv = bulv + fsign(bulv)*10.f;
        if(fabs(bulv) >= vmin){

            //std::cout<<"a: "<<bulv<<std::endl;
            bullet->push_back(Bullet());

            setStandardBullet("ressources/img/b4+t10.png");
            bullet->back().getSprite().setRotation((theta2-HALF_PI)*RAD_TO_DEG);
            bullet->back().getSprite().setColor(sf::Color(255*abs(bulv)/1000.f,128,255));
            if(bulv<0.f)
            bullet->back().getSprite().setColor(sf::Color(255*abs(bulv)/1000.f,255*abs(bulv)/1000.f,255));
            bullet->back().getSprite().move(pos);

            //std::cout<<"vit"<<bulv<<std::endl;
            bullet->back().setV(pos*bulv);
        }
    }
}

/** Generator 7 */

Generator7::Generator7(std::deque<Bullet>* blist):
    Generator(blist)
{
    rate = 1.0f;
    n = 50;
    a = 1.f;
    b = 6.f;
}

void Generator7::launch()
{
    float tempv = 200.f;
    float offset = -HALF_PI;

    for(int i=0;i<n;i++){
        float t = TWO_PI*i/n;
        float r=exp(cos(t))-2*cos(4*t)+pow(sin((2*t-PI)/24),5);
        sf::Vector2f pos(cos(t+offset), sin(t+offset));
        bullet->push_back(Bullet());
        /*TextureManager::assignTextureRect(bullet->back().getSprite(),"ressources/img/bullets1.png",4);*/
        setStandardBullet("ressources/img/b4+t10.png");
        bullet->back().getSprite().setColor(sf::Color(255,55,55));
        bullet->back().setV(pos*tempv*(1.f+r/3.f));
        bullet->back().getSprite().move(pos*r*2.f);
        //bullet->back().getSprite().move(10.f*sf::Vector2f(x,y));

    }
}

/** */

Generator8::Generator8(std::deque<Bullet>* blist):
    Generator(blist)
{
    rate = 0.9f;
    n = 100/2;
    a = 100.f;
    b = 60.f;
}

void Generator8::launch()
{
    float tempv = 250.f;
    float offset = -HALF_PI;

    for(int i=-n;i<n;i++){
        float t = (float)i/n;
        sf::Vector2f pos(cos(t+offset)*cos(t*(3+nblaunch%9)),cos(t*(1+nblaunch%5)) );
        if(fabs(pos.x)+fabs(pos.y) > 0.04f){
            bullet->push_back(Bullet());
            //TextureManager::assignTextureRect(bullet->back().getSprite(),"ressources/img/bullets1.png",4);//size 10x10
            setStandardBullet("ressources/img/bullets1.png",4);
            bullet->back().getSprite().setColor(sf::Color(255,55,55));
            bullet->back().setV(pos*tempv);
            //bullet->back().getSprite().move(a*t+sin(nblaunch*rate)*b, 0.f);
            //bullet->back().getSprite().move(10.f*sf::Vector2f(x,y));
        }
    }
}

/** */

Generator9::Generator9(std::deque<Bullet>* blist):
    Generator(blist)
{
    rate = 0.08f;
    n = 10;
    a = 100.f;
    b = 0.08f;
}

void Generator9::launch()
{
    float tempv = 250.f;
    //float offset = -HALF_PI;
    float t = sin(0.01f*nblaunch*PI);
    int m = n - t*t*n*0.9f;
    for(int i=0;i<m;i++){
        float theta = 2.f*PI*(i)/m+HALF_PI+nblaunch*PI*0.f;
        float theta2 = 0.02f*PI*nblaunch;
        float theta3 = b*PI*nblaunch;
        float te = (sin(theta3)*cos(theta2)-0.5f)*50.f;
        sf::Vector2f pos(cos(theta),sin(theta));
        sf::Vector2f pos2(cos(theta2),sin(theta2));
        sf::Vector2f pos3(cos(theta3),sin(theta3));

        bullet->push_back(Bullet());
        setStandardBullet("ressources/img/bullets1.png",4);
        bullet->back().getSprite().setColor(sf::Color(255,255*fabs(pos3.x),55));
        bullet->back().setV(pos*tempv);
        bullet->back().getSprite().move(pos2*50.f);
        bullet->back().getSprite().move(pos3*te);
    }
}

/** Gen 10 **/

Generator10::Generator10(std::deque<Bullet>* blist):
    Generator(blist)
{
    rate = 0.08f;
    n = 10;
    a = 100.f;
    b = 0.08f;
}

void Generator10::launch()
{
    const float alpha = 10.f;
    const float rateMin = 0.2f;
    const float rateMax = 0.4f;
    rate = Utils::tri(nblaunch,alpha)/alpha*(rateMax-rateMin)+rateMin;


    float tempv = 400.f;

    int m = 7;
    const sf::Vector2f offset(0.01f,0.15f);
    const float subdiv = Config::WINDOWS_HEIGHT*(1.f-offset.y*2.f)/(m-1.f);
    const float aperture = asin(subdiv/Config::WINDOWS_WIDTH) * 0.8f;
    for(int i=0;i<m;++i) {
        sf::Vector2f pos(Config::WINDOWS_WIDTH*offset.x,
                         Config::WINDOWS_HEIGHT*offset.y+i*subdiv);


        bullet->push_back(Bullet());
        bullet->back().getSprite().setOrigin(sf::Vector2f(bullet->back().getSprite().getLocalBounds().width/2.f,
                                                       bullet->back().getSprite().getLocalBounds().height/2.f));
        if(i%2 == 0){
            setStandardBullet("ressources/img/b7.png");
            pos.y -= cosf(nblaunch*TWO_PI*0.1f)*subdiv*0.6f/2.f;
            bullet->back().setV(sf::Vector2f(tempv,0));
        }else{
            pos.y += 4.f*cosf(nblaunch*TWO_PI*0.1f)*subdiv*0.2f/2.f;
            setStandardBullet("ressources/img/b6.png");

            float w = TWO_PI*0.4f*(float)nblaunch;

            w = Utils::tri(w,aperture)-aperture/2.f;
            sf::Vector2f v2(fabs(cosf(w)),sinf(w));
            bullet->back().getSprite().rotate(atan2f(v2.y,v2.x+0.000001f)*RAD_TO_DEG);
            bullet->back().setV(v2*tempv);
        }

        bullet->back().getSprite().rotate(90.f);
        bullet->back().getSprite().setPosition(pos);

    }
}

/** ------------------------------------------------------------------------- */
/** Generator 1 player version */

Generator1p::Generator1p(std::deque<Bullet>* blist):
    PlayerGenerator(blist)
{
    n = 1;
    rate = 0.3f;
}

Generator1p::Generator1p(std::deque<Bullet>* blist, float nrate, int nb):
    PlayerGenerator(blist)
{
    n = nb;
    rate = nrate;
}

void Generator1p::launch()
{
    for(int i=0; i<n; i++) {
        float theta = PI*(i+1)/(float)(n+1)+sprite.getRotation()/RAD_TO_DEG;
        float r = 40.f;
        sf::Vector2f pos(cos(theta), sin(theta));

        bullet->push_back(Bullet());
        //TextureManager::assignTextureRect(bullet->back().getSprite(),"ressources/img/bullets1.png",1);
        setStandardBullet("ressources/img/bullets1.png",1);
        bullet->back().getSprite().setColor(sf::Color(105,250,100));
        bullet->back().getSprite().setOrigin(sf::Vector2f(bullet->back().getSprite().getLocalBounds().width/2.f,
                                                          bullet->back().getSprite().getLocalBounds().width/2.f));
        //bullet->back().getSprite().setPosition(sprite.getPosition());
        bullet->back().getSprite().move(
            sf::Vector2f(sprite.getLocalBounds().width,sprite.getLocalBounds().height)/-2.f);
        bullet->back().getSprite().move(r*pos);
        bullet->back().getSprite().setRotation((-HALF_PI+theta)*RAD_TO_DEG);
        bullet->back().setV(pos*500.f);
    }
}

void Generator1p::improve(int mode, int fact){
    fact = fact;
    if(mode == PlayerGenerator::RATE){
        rate /= 2.f;
        if(rate < 0.05f)
            rate = 0.05f;
    }
}


/** Generator 2 for player */

const float Generator2p::minRate = 0.03f;

Generator2p::Generator2p(std::deque<Bullet>* blist):
    PlayerGenerator(blist), count(0)
{
    n = 1;
    rate = 0.1f;
    radiusMin = 20.f;
}

Generator2p::Generator2p(std::deque<Bullet>* blist, float nrate, int nb, float radiusMinimum):
    PlayerGenerator(blist), count(0)
{
    n = nb;
    rate = nrate;
    radiusMin = radiusMinimum;
}

void Generator2p::launch()
{
    count++;
    if(count > 5){
        bullet->push_back(Bullet());
        TextureManagerGlobal::assignTextureRect(bullet->back().getSprite(),"ressources/img/bullets1.png",2);
        bullet->back().getSprite().setColor(sf::Color(85,225,100));
        bullet->back().getSprite().setOrigin(sf::Vector2f(bullet->back().getSprite().getLocalBounds().width/2.f,
                                                          bullet->back().getSprite().getLocalBounds().width/2.f));
        bullet->back().getSprite().setPosition(sprite.getPosition());
        bullet->back().getSprite().setRotation(-PI*RAD_TO_DEG);
        bullet->back().setV(0.f,-500.f);
        count = 0;
    }

    for(int i=0; i<n; i++) {
        float theta = TWO_PI*i/n+sprite.getRotation()/RAD_TO_DEG+nblaunch*rate*TWO_PI*0.8f;
        float r = radiusMin*(1.f+0.1f*sin(nblaunch*rate*TWO_PI*1.1f) );

        sf::Vector2f pos( cos(theta),  sin(theta));

        bullet->push_back(Bullet());
        TextureManagerGlobal::assignTextureRect(bullet->back().getSprite(),"ressources/img/bullets1.png",4);
        //bullet->back().getSprite().setTexture(*TextureManagerGlobal::getTexture("ressources/img/b4+t10.png"));
        bullet->back().getSprite().setColor(sf::Color(155,250,100,120));
        bullet->back().getSprite().setOrigin(sf::Vector2f(bullet->back().getSprite().getLocalBounds().width/2.f,
                                                          bullet->back().getSprite().getLocalBounds().width/2.f));
        bullet->back().getSprite().setPosition(sprite.getPosition());
        bullet->back().getSprite().move(
            sf::Vector2f(sprite.getLocalBounds().width,sprite.getLocalBounds().height)/-2.f);
        bullet->back().getSprite().move(r*pos);
        bullet->back().getSprite().setRotation(-PI*RAD_TO_DEG);
        bullet->back().setV(0.f,-500.f);
    }
}

void Generator2p::improve(int mode, int fact){
    fact = fact;
    if(mode == PlayerGenerator::RATE){
        rate *= 2.f/3.f;
        if(rate < minRate)
            rate = minRate;
    }
}


