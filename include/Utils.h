#ifndef UTILS_H
#define UTILS_H

#define GOLDEN_ANGLE 2.39996322f
#define RAD_TO_DEG 57.2957795f
#define DEG_TO_RAD 0.0174532925f
#define HALF_PI 1.57079632679f
#define PI 3.14159265f
#define TWO_PI 6.28318530718f

#include <string>
#include <sstream>
#include <cmath>

/** Identity function: x -> x*/
float id(float val);

/** Convert any possible type to string */
template<typename T>
std::string ttos( T t )
{
   std::stringstream ss;
   std::string s;
   if(ss << t){
   ss >> s;
   return s;
   }
   return "";
}

/** Convert any string to any T type */
template <typename T>
T stot( std::string s )
{
    std::stringstream ss( s );
    T t;
    ss >> t;
    return t;
}

/** return 1.f is positive, -1.f otherwise */
inline static float fsign(float x){
    return (x > 0.f) ? 1.f : -1.f;
}

/** return 1 is positive, -1 if negative and 0 else */
inline static int isign(float x){
    return (x > 0) ? 1 : (x==0) ? 0 : -1;
}

#include <SFML/Graphics.hpp>

namespace Utils {
    /*static int log10(int x){
        int res = 0;
        while(1){
            res++;
            x /= 10;
            if(x==0) break;
        }
        return res;
    }*/
    /*inline float function_inv(float x, const float a)
    {
        return (1+a)*x/(1+a*x);
    }*/

    extern unsigned int WINDOWS_WIDTH;
    extern unsigned int WINDOWS_HEIGHT;

    /** Float modulo operation
    * example : 3.4f % 3.0f = 0.4f */
    inline float mod(float n, float mod)
    {
        int a = n/mod;
        return n-a*mod;
    }

    /** triangle function */
    inline float tri(float n, float mod)
    {
        int a = (n)/(2.f*mod);
        return mod-fabs(n-a*2.f*mod-mod);
    }

    /** test if point is strictly in the circle p_circle of radius r */
    inline bool inCircle(sf::Vector2f point, sf::Vector2f p_circle,
                            float radius)
    {
        return (point.x-p_circle.x)*(point.x-p_circle.x)+
            (point.y-p_circle.y)*(point.y-p_circle.y) < radius*radius;
    }
    /** cosinus interpolation between point between y1 and y2 */
    float cosineInterpolate(float y1, float y2, float x);
    /** Interpolate an array of points with cos interpolation 
    * by adding "subdivision" points between to points */
    std::vector<sf::Vector2f> getInterpolationCosine(std::vector<sf::Vector2f> const& path, unsigned int subdivision);
    /** Get relative positions of points on the array (the first point keep its absolute position) */
    std::vector<sf::Vector2f> getPathFractionned(std::vector<sf::Vector2f> const& path);
}


#endif
