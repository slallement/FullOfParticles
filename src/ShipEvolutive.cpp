#include "../include/ShipEvolutive.h"

ShipEvolutive::ShipEvolutive(Ship* ref, std::string n) :
    body(ref), name(n), time(0.f), t1(10.f), currentGene(0), bulletPlayer(NULL)
{
    std::string path = "ressources/data/species/"+name;
    std::ifstream fs(path.c_str());
    if(fs.is_open()){
        fs.close();
        readGenome(name);
    }else{
        initRandom();
    }
}

ShipEvolutive::ShipEvolutive(ShipEvolutive & ref, gene* chromosomes) :
    body(ref.body), name(ref.name), time(0.f), t1(10.f),
    generation(ref.generation), currentGene(0), bulletPlayer(ref.bulletPlayer)
{
    for(int i=0;i<nbgene;i++){
        chrom[i] = chromosomes[i];
    }
}

ShipEvolutive::~ShipEvolutive() {}

void ShipEvolutive::initRandom()
{
    generation = 0;
    for(int i=0;i<nbgene; i++){
        randomiseGene(i);
    }
}

inline void ShipEvolutive::randomiseGene(int i)
{
    chrom[i].f = rand()%(nbact+1);
    chrom[i].time = (0.4f*(float)rand())/(float)RAND_MAX;
    chrom[i].strength = (float)rand()/(float)RAND_MAX;
    chrom[i].next = (i+1+((rand()%100<30)?SHIPEVOLUTIVE_SIZE:0))%nbgene;
}

inline void ShipEvolutive::randomiseGeneSoft(int i)
{
    int r = rand()%101;
    if(r > 50)
        chrom[i].f = rand()%(nbact+1);
    chrom[i].time = (1.f*(float)rand())/(float)RAND_MAX;
    if(r>50)
        chrom[i].strength = (float)rand()/(float)RAND_MAX;
    if(r > 40)
        chrom[i].next = rand()%nbgene;
}

void ShipEvolutive::update(float dt)
{
    time += dt;
    if(bulletPlayer->size()>1){
        float d = fabs(body->getSprite().getPosition().x-(*bulletPlayer)[0].getSprite().getPosition().x);
        if(d < 50.f)
            timebul += dt;
    }
    t1 += dt;
    if(t1 > chrom[currentGene].time){
        //std::cout<<"ok"<<currentGene<<std::endl;
        act(chrom[currentGene].f,chrom[currentGene].strength);
        currentGene = chrom[currentGene].next;
        t1 -= chrom[currentGene].time;
    }
}

void ShipEvolutive::reset()
{
    time = 0.f;
    t1 = 10.f;
    currentGene = 0;
}

ShipEvolutive::Crossed ShipEvolutive::crossover(ShipEvolutive& s1, ShipEvolutive& s2)
{
    Crossed nchrom;

    int cut = rand()%nbgene;
    if(rand()%100<probcross) cut = 0;
    for(int i=0;i<nbgene;i++){
        if(i<cut){
            nchrom.a[i] = s1.chrom[i];
            nchrom.b[i] = s2.chrom[i];
        }else{
            nchrom.a[i] = s2.chrom[i];
            nchrom.b[i] = s1.chrom[i];
        }
    }
    return nchrom;
}

float ShipEvolutive::reproduction(std::vector<ShipEvolutive> & evo)
{
    sort(evo.begin(),evo.end(),ShipEvolutive::comp);
    int mutfact = 1+5*50/evo.begin()->time;
        for(unsigned int i=evo.size()/2-1;i>2;i--){
            int id = 2*i;
            ShipEvolutive::Crossed doublet = crossover(evo[evo.size()/2-i],evo[evo.size()/2-i+1]);
            evo[id] = ShipEvolutive(evo[id],doublet.a);
            evo[id+1] = ShipEvolutive(evo[id+1],doublet.b);
            evo[id].mutation();
            evo[id+1].mutation();
            evo[id].generation+=1;
            evo[id+1].generation+=1;
        }
        int id = evo.size()-1;
        evo[id] = ShipEvolutive(evo[id],evo[0].chrom);
        evo[id].mutation(mutfact);

    return evo.begin()->time;
}

void ShipEvolutive::mutation(int p)
{
    for(int i=0;i<nbgene/2;i++){
        int idg = (int)rand()%nbgene;
        if(rand()%100 > probmutation*p){
            randomiseGeneSoft(idg);
        }
    }
}


void ShipEvolutive::act(int f, float s)
{
    switch(f){
        case 1 :
                body->setVx(-s*body->getVelocity());
            break;
        case 2 :
                body->setVx(s*body->getVelocity());
            break;
        case 3 :
                body->setVy(-s*body->getVelocity());
            break;
        case 4 :
                body->setVy(s*body->getVelocity());
            break;
        case 5 :
                body->addVy((s-0.5f)*2.f*body->getVelocity());
                body->clampV();
            break;
        case 6 :
                body->addVx((s-0.5f)*2.f*body->getVelocity());
                body->clampV();
            break;
        case 7:
                body->addVx(s*body->getV().x);
                body->clampV();
            break;
        case 8:
                body->addVy(s*body->getV().y);
                body->clampV();
            break;
        case 9:
                body->addVx(-s*body->getV().x);
                body->clampV();
            break;
        case 10:
                body->addVy(-s*body->getV().y);
                body->clampV();
            break;
        case 11:
            goFurther3(-s,3,3);
        case 12:
            goFurther3(-s,1,3);
        case 13:
            goFurther3(-s,2,3);
            break;
        case 14:
            goFurther2(s,0);
            break;
        case 15:
            goFurther1(s);
            break;
        case 16:
            goFurther1(1.f);
            break;
        case 17:
            goFurther3(s,1,3);
            break;

        default:
            break;
    }

}

void ShipEvolutive::goFurther1(float s)
{
    for(unsigned int i=1;i<bulletPlayer->size();++i){
        sf::Vector2f posbul = body->getSprite().getPosition()
            -(*bulletPlayer)[i].getSprite().getPosition();
        float dist = posbul.x*posbul.x+posbul.y*posbul.y;
        if(dist < 700.f*700.f && dist > 0.0001f){
            sf::Vector2f orthoV = (*bulletPlayer)[i].getV();
            orthoV = sf::Vector2f(-orthoV.y,orthoV.x);
            dist = sqrtf(dist+0.00001f);
            body->addV(orthoV*s*body->getVelocity()/dist);
        }
    }
    body->clampV();
}

void ShipEvolutive::goFurther2(float s, int id)
{
    if(fabs(s) < 0.01f) s += fsign(s)*0.5f;

    for(unsigned int i=1;i<bulletPlayer->size()/(id+1);++i){
        sf::Vector2f posbul = body->getSprite().getPosition()
            -(*bulletPlayer)[i].getSprite().getPosition();
        float dist = posbul.x*posbul.x+posbul.y*posbul.y;
        if(dist < 200.f*200.f && dist > 0.0001f){
            dist = sqrtf(dist);
            body->addV(10.f*posbul*s*body->getVelocity()/dist);
        }
    }
    body->clampV();
}

void ShipEvolutive::goFurther3(float s, int id, int id2)
{
    if(id2==0)
        return;
    if(bulletPlayer->size()/id2 != 0){
        id = rand()%(bulletPlayer->size()/id2)+bulletPlayer->size()*id/id2;
        if(id < (int)bulletPlayer->size()){
            sf::Vector2f posbul = body->getSprite().getPosition()
                -(*bulletPlayer)[id].getSprite().getPosition();
            float dist = posbul.x*posbul.x+posbul.y*posbul.y;
            float d2 = fabs(posbul.x)+fabs(posbul.y);
            if(d2 == 0.f) d2 = 0.1f;
            dist = 0.5f*(d2+dist/d2);
            //std::cout<<dist<<" diff"<<sqrt(posbul.x*posbul.x+posbul.y*posbul.y)<<std::endl;
            body->addV(s*posbul/(0.0001f+dist)*body->getVelocity());
            body->clampV();
        }
    }
}

void ShipEvolutive::writeGenome(std::string path)
{
    path = "ressources/data/species/"+path;
    std::ofstream fs(path.c_str(), std::ios::out | std::ios::binary);
    fs.write(reinterpret_cast<const char*>(&generation), sizeof (int16_t) );
    if(fs.is_open()){
        for(int i=0;i<nbgene; i++){
            fs.write(reinterpret_cast<const char*>(&chrom[i]), sizeof (gene) );
        }
        fs.close();
    }

    sf::Image image;
    image.create(SHIPEVOLUTIVE_SIZE,SHIPEVOLUTIVE_SIZE, sf::Color::Black);
    for(int j=0;j<SHIPEVOLUTIVE_SIZE;j++){
        for(int i=0;i<SHIPEVOLUTIVE_SIZE;i++){
            int lumi = chrom[i+SHIPEVOLUTIVE_SIZE*j].strength*255;
            sf::Color color(lumi,lumi,lumi);
            color.r *= (chrom[i+SHIPEVOLUTIVE_SIZE*j].f==2)? 0 : 1;
            color.g *= ( (chrom[i+SHIPEVOLUTIVE_SIZE*j].f>=17 &&
                        chrom[i+SHIPEVOLUTIVE_SIZE*j].f<=20)
                        )? 0 : 1;
            color.b *= (chrom[i+SHIPEVOLUTIVE_SIZE*j].f==2)? 0 : 1;
            image.setPixel(i, j, color);
        }
    }
    image.saveToFile(path+".png");
}

void ShipEvolutive::writeGenome()
{
    writeGenome(name);
}

void ShipEvolutive::readGenome(std::string path)
{
    path = "ressources/data/species/"+path;
    std::ifstream fs(path.c_str(), std::ios::in | std::ios::binary);
    fs.read(reinterpret_cast<char*>(&generation), sizeof (int16_t) );
    for(int i=0;i<nbgene; i++){
        fs.read(reinterpret_cast<char*>(&chrom[i]), sizeof (gene) );
    }
    fs.close();
}



