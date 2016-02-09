#ifndef BIGIMAGE_H
#define BIGIMAGE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>

/** A class to manage big textures (like thoses used for the background) */
class BigImage : public sf::Drawable, public sf::Transformable
{
    public:
        BigImage();
        BigImage(std::string imagepath);
        virtual ~BigImage();
        BigImage(sf::Image & img);
        /** Load an image and slice it in nsize*nsize sub textures */
        void load(sf::Image const& img, int nsize=1024*2);
        /*void setWindowSize(sf::Vector2u const& win){
            onscreenx = ceil((float)win.x/size)+1;
            onscreeny = ceil((float)win.y/size)+1;
        }*/
        /** Scroll on the y axis from "step" pixels */
        void scroll(float step);
        /** Scroll on the x axis from "step" pixels */
        void scrollHor(float step);

    protected:
        std::vector<sf::Texture> texture;
        sf::VertexArray plane;
        int slicex;
        int slicey;
        int size;
        sf::Vector2f pos;
        int offsety;
        int offsetx;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            //states.transform *= getTransform();
            states.transform.translate((int)pos.x,(int)pos.y);

            int j,i;

            for(j=0;j<slicey;j++){
                int idY = ((j-offsety>=0) ? j-offsety : j-offsety+slicey)*slicex;
                for(i=0;i<slicex;i++){
                    int idX = ((i-offsetx>=0) ? i-offsetx : i-offsetx+slicex);
                    states.texture = &texture[idY+idX];
                    target.draw( &plane[(i + j*(slicex+1) ) * 4], 4,sf::Quads,states);
                }
            }
            if(pos.y>0){
                j = -1;
                int idY = ((j-offsety>=0) ? j-offsety : j-offsety+slicey) * slicex;
                for(i=0;i<slicex;i++){
                    int idX = ((i-offsetx>=0) ? i-offsetx : i-offsetx+slicex);
                    states.texture = &texture[idY+idX];
                    target.draw( &plane[(i + slicey*(slicex+1) ) * 4], 4, sf::Quads,states);
                }
            }
            if(pos.x>0){
                i = -1;
                int idX = ((i-offsetx>=0) ? i-offsetx : i-offsetx+slicex);
                for(j=0;j<slicey;j++){
                    int idY = ((j-offsety>=0) ? j-offsety : j-offsety+slicey)*slicex;
                    states.texture = &texture[idY+idX];
                    target.draw( &plane[(slicex + j*(slicex+1) ) * 4], 4, sf::Quads,states);
                }

                i = -1;j = -1;
                idX = ((i-offsetx>=0) ? i-offsetx : i-offsetx+slicex);
                int idY = ((j-offsety>=0) ? j-offsety : j-offsety+slicey) * slicex;
                states.texture = &texture[idY+idX];
                target.draw( &plane[(slicex + slicey*(slicex+1) ) * 4], 4, sf::Quads,states);
            }

        }

};

#endif // BIGIMAGE_H
