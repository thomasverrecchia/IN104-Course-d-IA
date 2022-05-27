#include "pod.h"
#include "game.h"
#include <SFML/System/Vector2.hpp>

Decision::Decision(sf::Vector2f target, float power) : target_(target), power_(power)
{
    target_ = target;
    power_ = power;
};

Pod::Pod(sf::Vector2f pos, float angle, sf::Vector2f vel) 
{
    pos_ = pos;
    angle_ = angle;
    vel_ = vel;
};




Decision Pod::getDecision(Game myGame) const
{  

    if (nextCP_ == 0)
        {
            sf::Vector2f target = myGame.finalCP_.getPosition();
            
            return Decision(target, 50);


        } 
    else
        {
            sf::Vector2f target = myGame.otherCPs_[nextCP_-1.f].getPosition();
                
            return Decision(target, 50);
        } 
};