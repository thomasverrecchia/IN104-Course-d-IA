#include "game.h"
#include "checkpoint.h"
#include "pod.h"
#include "utils.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <cmath>

#include <string>

#include <ios>
#include <iostream>

Game::Game() : finalCP_({0,0},0)
{
    if (!backgroundTexture_.loadFromFile("/home/ensta/IN104/repository/Images/background.png"))
    {
        printf("backgroundTexture error\n");
    }
    //backgroundTexture_.setSmooth(true);
    backgroundSprite_.setTexture(backgroundTexture_);
    setOriginToCenter(backgroundSprite_);
    scaleToMinSize(backgroundSprite_,WIDTH_VIEW,HEIGHT_VIEW);
    backgroundSprite_.setPosition(WIDTH_VIEW/2.f,HEIGHT_VIEW/2.f);

}

Game::Game(std::vector<sf::Vector2f> checkpointsPositions) : finalCP_(checkpointsPositions[0],0)
{
    if (!backgroundTexture_.loadFromFile("/home/ensta/IN104/repository/Images/background.png"))
    {
        printf("backgroundTexture error\n");
    }
    //backgroundTexture_.setSmooth(true);
    backgroundSprite_.setTexture(backgroundTexture_);
    setOriginToCenter(backgroundSprite_);
    scaleToMinSize(backgroundSprite_,WIDTH_VIEW,HEIGHT_VIEW);
    backgroundSprite_.setPosition(WIDTH_VIEW/2.f,HEIGHT_VIEW/2.f);

    otherCPs_.reserve(checkpointsPositions.size()-1);
    for (unsigned int cpID = 1; cpID<checkpointsPositions.size(); cpID++)
    {
        otherCPs_.emplace_back(checkpointsPositions[cpID], cpID);
    }
}

void Game::addPod()
{
    int nb_pods = 2; // Nb de pods désirés

    // Création de l'espace de stockage
    pods_.reserve(nb_pods);
    podsSprites_.reserve(nb_pods);
    podsTextures_.reserve(nb_pods);

    // Création du Pod1

    Pod pod1 = Pod({1000,7000},0.f);
    sf::Texture pod1Texture_;
    sf::Sprite pod1Sprite_;
    if (!pod1Texture_.loadFromFile("/home/ensta/IN104/repository/Images/SWAnakinsPod.png"))
    {
        printf("pod1Texture error\n");
    }

    pods_.emplace_back(pod1);
    podsTextures_.emplace_back(pod1Texture_);
    podsSprites_.emplace_back(pod1Sprite_);


    // Création Pod2

    Pod pod2 = Pod({900,6800},0.f);
    sf::Texture pod2Texture_;
    sf::Sprite pod2Sprite_;
    if (!pod2Texture_.loadFromFile("/home/ensta/IN104/repository/Images/BSGCylon.png"))
    {
        printf("pod2Texture error\n");
    }

    pods_.emplace_back(pod2);
    podsTextures_.emplace_back(pod2Texture_);
    podsSprites_.emplace_back(pod2Sprite_);

    for(int i=0; i<nb_pods; i++){

        //Chargement et centrage de chaque pod
        podsSprites_[i].setTexture(podsTextures_[i]);
        setOriginToCenter(podsSprites_[i]);
        scaleToMinSize(podsSprites_[i],400,400);

        pods_[i].nextCP_ = 1;
        pods_[i].lapCount_ = 1;
    }
}

void Game::updatePhysics(int p)
{
    int c = 0; //Compteur pour n'ajouter des modifications qu'au premier Pod

    for (Pod &pod : pods_)
    {
        Decision d = pod.getDecision(*this);

        float alpha = 0.85;
        
        if(c == 0){ // Condition pour ne faire varier la vitesse uniquement du Pod1
            if (p == 1)    // augmentation de la vitesse lorsqu'on appuie sur la flèche du haut
            {
                d.power_ = fmin( 2 * d.power_,100) ;
            }

            if (p == 2)    // diminution de la vitesse lorsqu'on appuie sur la flèche du bas
            {
                d.power_ =  fmin(d.power_ / 2, 100);
            }
        }
        


        pod.vel_ = alpha * (pod.vel_ + d.power_ * (d.target_ - pod.pos_)/norm((d.target_ - pod.pos_)));
        pod.pos_ = pod.pos_ + pod.vel_;
        pod.angle_ = arg(pod.vel_);

        
        // Le Pod comprend qu'il passe par un CP
        

        if (norm(pod.pos_ - d.target_)<550){ 
            
            if (pod.nextCP_ == 0 && pod.lapCount_< NUMBER_OF_LAPS){
                pod.nextCP_ = 1;
                pod.lapCount_ += 1;
            }
            else if (0 < pod.nextCP_ && pod.nextCP_ < otherCPs_.size()) pod.nextCP_ += 1;
            else{
                pod.nextCP_ = 0; //FinalCP         
            }
        }   
    c += 1;
    }
}

void Game::updateGraphics(sf::Time frameTime)
{
    
    float k = (physicsTime - frameTime)/(frameTime-lastFrameTime); 
    
    int nb_pods = podsSprites_.size();
    for (int i=0; i<nb_pods; ++i)
    {
        sf::Vector2f pos_sprite = podsSprites_[i].getPosition();

        if (k>1)  podsSprites_[i].setPosition( pos_sprite + (pods_[i].pos_ - pos_sprite)/k );
        else podsSprites_[i].setPosition(pods_[i].pos_);
        
        podsSprites_[i].setRotation(pods_[i].angle_*180.f/M_PI);
    }
    lastFrameTime = frameTime;
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backgroundSprite_, states);
    target.draw(finalCP_, states);
    

    for (const auto &cp : otherCPs_)
    {
        target.draw(cp, states);
    }

    for (const auto &podSprite : podsSprites_)
    {
        target.draw(podSprite, states);
    }

    
}