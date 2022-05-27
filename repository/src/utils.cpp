#include "utils.h"
#include <cmath>

void setOriginToCenter(sf::Sprite &object)
{
    auto rect = object.getGlobalBounds();
    object.setOrigin(rect.width/2., rect.height/2.);
}

void setOriginToCenter(sf::Shape &object)
{
    auto rect = object.getGlobalBounds();
    object.setOrigin(rect.width/2., rect.height/2.);
}

void scaleToMinSize(sf::Sprite &sp, double size_x, double size_y)
{
    double scalingFactor = std::max(size_x/sp.getTextureRect().width, size_y/sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

void scaleToMaxSize(sf::Sprite &sp, double size_x, double size_y)
{
    double scalingFactor = std::min(size_x/sp.getTextureRect().width, size_y/sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

void scaleByRadius(sf::Sprite &sp, int radius)
{
    double scalingFactor = 2*radius/std::sqrt(sp.getTextureRect().width*sp.getTextureRect().width + sp.getTextureRect().height*sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

void setTextCenterPosition(sf::Text &txt, sf::Vector2f center)
{
    sf::Vector2f offset;
    offset.x = txt.getPosition().x - txt.getGlobalBounds().left - txt.getGlobalBounds().width/2.;
    offset.y = txt.getPosition().y - txt.getGlobalBounds().top - txt.getGlobalBounds().height/2.;

    txt.setPosition(center + offset);
}

float norm(sf::Vector2f u){ // calul la norme d'un vecteur
    return sqrt(pow(u.x,2) + pow(u.y,2));
}


float arg(sf::Vector2f u){ // calcul angle
    if (u.x == 0) return M_PI/2;
    if (u.x < 0) return atan(u.y/u.x)+M_PI;
    else return atan(u.y/u.x);
}

std::vector<sf::Vector2f> coord_CP(int nbCP){

    std::vector<sf::Vector2f> Coord_CP;

    if (nbCP == 9)
        nbCP = rand()%7 + 2;
        
    Coord_CP.reserve(nbCP+1);

    
    for (int i=0; i<nbCP+1; ++i)
    {
        bool collision;
        float x;
        float y;
        do{
            x = rand()%14801 + 600; // x dans [600,15400]
            y = rand()%7801 + 600; // y dans [600, 8400]
            collision = false;
            
            // Verification d'une eventuelle collision
            for(int j=0; j<i; ++j){
                if (norm(sf::Vector2f(x,y)-Coord_CP[j])<1200)
                {   collision = true;
                }    
            }
        } while (collision);
        
        //Si pas de collision, on ajoute les coordonnees du CH
        Coord_CP.emplace_back(sf::Vector2f(x,y));
    }
    return Coord_CP;
}