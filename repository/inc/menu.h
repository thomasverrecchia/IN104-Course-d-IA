#ifndef INC_MenuLOGIC_H
#define INC_MenuLOGIC_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>



class Menu : public sf::Drawable
{
    public :
    Menu(); 


    
    private :
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture menuTexture_;
    sf::Sprite menuSprite_;

    sf::Sprite jouerSprite_;
    sf::Texture jouerTexture_;

    sf::Sprite crossSprite_;  // On voulait sprite une croix pour faire des tests. Inutilisé dans le rendu final
    sf::Texture crossTexture_;


    sf::Time lastFrameTime;
    sf::Time physicsTime;   
};

#endif