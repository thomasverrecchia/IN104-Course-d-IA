#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cmath>
#include "game.h"
#include "checkpoint.h"
#include "utils.h"
#include <vector>
#include <string>

#include "menu.h"

int main()
{
    int nbCP = 6; // On fixe 6 checkpoints
    std::vector<sf::Vector2f> Coord_CP = coord_CP(nbCP);
    int en_jeu = 0;  // variable quivaut 0 pour le menu et 1 lorsque le jeu tourne


    Game myGame = Game(Coord_CP);
    


    sf::RenderWindow window(sf::VideoMode(16000, 9000), "STAR WARS RACE", sf::Style::Default);
    window.setView(sf::View(sf::Rect(0.f,0.f,16000.f,9000.f)));

    //frame per second
    float fps = 60;
    //temps minimal entre deux frame
    sf::Time refreshTime = sf::microseconds(1e6/fps);

    //horloge depuis le début du jeu
    sf::Clock globalClock;
    //horloge réinitialisée à chaque frame
    sf::Clock refreshClock;

    //temps de la physique du jeu
    sf::Time physicsTime = sf::Time::Zero;

    //Vous pouvez aussi initialiser myGame avec une liste de checkpoints prédéfinie
    //Game myGame;
    myGame.addPod();

    while (window.isOpen())
    {
        sf::Event event;

        if (en_jeu == 0) // Dans le menu
        {
            Menu menu = Menu();
            while(en_jeu == 0)
            {
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                       en_jeu = -1;
                        window.close();
                    } 

                    if(event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            int x = event.mouseButton.x;
                            int y = event.mouseButton.y;

                            //Boutton Jouer du Menu qui active le jeu lorsqu'on clic dessus
                            if (1237<x && x<1552 && 720<y && y<805)
                            {
                                en_jeu = 1;
                            }
                        }
                    }  
                } 

                window.clear();
                //
                window.draw(menu);
                //
                window.display();   
            }    
        }

        if (en_jeu == 1) // Dans la course
        {

            int p = 0; // Paramètre permettant de faire varier le power du pod

            //si on a dépassé le refreshTime depuis la dernière frame
            if (refreshClock.getElapsedTime() >= refreshTime)
            {
                //réinitialise l'horloge qui mesure le temps entre les frames
                refreshClock.restart();

                //récupère le temps écoulé depuis le début du jeu
                sf::Time frameTime = globalClock.getElapsedTime();

                //si on a dépassé le temps de la physique
                if (frameTime > physicsTime)
                {

                    while (window.pollEvent(event)) // Evènements effectués par l'utilisateur pendant la course
                    {
                    
                        if(event.type == sf::Event::KeyPressed)
                        {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // flèche du haut augmente la vitesse
                            {
                            p = 1;
                            }
                        }  

                        if(event.type == sf::Event::KeyPressed)
                        {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) // flèche du bas diminue la vitesse
                            {
                            p = 2;
                            }
                        } 
                    }

                    //met à jour les sprite au temps de la physique
                    myGame.updateGraphics(physicsTime);
                    //fait avancer la physique d'un pas de temps
                    myGame.updatePhysics(p);
                    physicsTime += PHYSICS_TIME_STEP;

                    //reprend le temps écoulé depuis le début pour rester précis
                    frameTime = globalClock.getElapsedTime();
                }

            
                //met à jour les sprites au temps actuel
                myGame.updateGraphics(frameTime);
                window.clear();
                window.draw(myGame);
                window.display();
            }
        }
    }

    return 0;
}









