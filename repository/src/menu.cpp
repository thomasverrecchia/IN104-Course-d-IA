#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "menu.h"
#include "utils.h"
#include "game.h"


Menu::Menu()
{
    if (!menuTexture_.loadFromFile("/home/ensta/IN104/repository/Images/Menu.png"))
    {
        printf("menuTexture error\n");
    }

    menuSprite_.setTexture(menuTexture_);
    setOriginToCenter(menuSprite_);
    scaleToMinSize(menuSprite_,WIDTH_VIEW,HEIGHT_VIEW);
    menuSprite_.setPosition(WIDTH_VIEW/2.f,HEIGHT_VIEW/2.f);

    if (!jouerTexture_.loadFromFile("/home/ensta/IN104/repository/Images/jouer.png"))
        printf("error");
    jouerSprite_.setTexture(jouerTexture_);
    setOriginToCenter(jouerSprite_);
    scaleToMaxSize(jouerSprite_,3000.f, 3000.f);
    jouerSprite_.setPosition(12060.f, 7560.f);
//x = 12060 & y =7560
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(menuSprite_, states);
    target.draw(jouerSprite_, states);
}
