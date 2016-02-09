#include "../include/BigImage.h"

BigImage::BigImage():
    slicex(0),slicey(0),pos(0.f,0.f),offsety(0),offsetx(0)
{
}

BigImage::BigImage(std::string filepath):
    slicex(0),slicey(0),pos(0.f,0.f),offsety(0),offsetx(0)
{
    sf::Image img;
    if(!img.loadFromFile(filepath)){
        //erreur
    }else{
        load(img);
    }
}

BigImage::BigImage(sf::Image & img):
    slicex(0),slicey(0),pos(0.f,0.f),offsety(0),offsetx(0)
{
    load(img);
}

BigImage::~BigImage()
{
}

void BigImage::load(sf::Image const& img, int nsize)
{
    size = nsize;
    slicex = (int)ceil((float)img.getSize().x/size);
    slicey = (int)ceil((float)img.getSize().y/size);

    texture.resize(slicex*slicey);
    for(int j=0;j<slicey;j++){
        for(int i=0;i<slicex;i++){
            sf::IntRect zone = sf::IntRect(size*i,size*j,size*(i+1),size*(j+1));
            if(!texture[j*slicex+i].loadFromImage(img,zone)){
                // error
            }
        }
    }
    plane.setPrimitiveType(sf::Quads);
    plane.resize((slicex+1)*(slicey+1)*4);

    int j,i;

    for(j=0;j<slicey;j++){
        for(i=0;i<slicex;i++){
            sf::Vertex* quad = &plane[(i + j * (slicex+1)) * 4];

            quad[0].position = sf::Vector2f(size*i,size*j);
            quad[1].position = sf::Vector2f(size*(i+1),size*j);
            quad[2].position = sf::Vector2f(size*(i+1),size*(j+1));
            quad[3].position = sf::Vector2f(size*i,size*(j+1));
        }
    }
    j = slicey;
    for(i=0;i<slicex;i++){
        sf::Vertex* quad = &plane[(i + j * (slicex+1)) * 4];
        quad[0].position = sf::Vector2f(size*i,-size);
        quad[1].position = sf::Vector2f(size*(i+1),-size);
        quad[2].position = sf::Vector2f(size*(i+1),0);
        quad[3].position = sf::Vector2f(size*i,0);
    }
    i = slicex;
    for(j=0;j<slicey;j++){
        sf::Vertex* quad = &plane[(i + j * (slicex+1)) * 4];

        quad[0].position = sf::Vector2f(-size,size*j);
        quad[1].position = sf::Vector2f(0,size*j);
        quad[2].position = sf::Vector2f(0,size*(j+1));
        quad[3].position = sf::Vector2f(-size,size*(j+1));
    }
    {
        sf::Vertex* quad = &plane[(slicex + slicey * (slicex+1)) * 4];

        quad[0].position = sf::Vector2f(-size,-size);
        quad[1].position = sf::Vector2f(0,-size);
        quad[2].position = sf::Vector2f(0,0);
        quad[3].position = sf::Vector2f(-size,0);
    }

    for(i=0;i<(slicex+1)*(slicey+1);i++){
        plane[4*i  ].texCoords = sf::Vector2f(0,0);
        plane[4*i+1].texCoords = sf::Vector2f(size,0);
        plane[4*i+2].texCoords = sf::Vector2f(size,size);
        plane[4*i+3].texCoords = sf::Vector2f(0,size);
    }

}

void BigImage::scroll(float step){
    pos.y += step;
    if(pos.y<0){
        pos.y = size;
        offsety--;
        if(offsety<0){
            offsety = slicey-1;
        }
    }else if(pos.y>=(float)size){
        offsety++;
        pos.y-=size;
        if(offsety>=slicey)
            offsety = 0;
    }
}

void BigImage::scrollHor(float step){
    pos.x += step;
    if(pos.x<0){
        pos.x = size;
        offsetx--;
        if(offsetx<0)
            offsetx = slicex-1;
    }else if(pos.x>=(float)size){
        offsetx++;
        pos.x-=size;
        if(offsetx>=slicex)
            offsetx = 0;
    }
}
