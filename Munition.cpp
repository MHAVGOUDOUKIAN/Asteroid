/** Auteur: Maxime HAVGOUDOUKIAN
 *  
 *  Nom Projet: Asteroid 
 * 
 *  Date de création: 09/04/2021
 *  Dernière modification: 09/04/2021
 *  
**/
#include "Munition.hpp"

Munition::Munition(const float x, const float y, const float angle /* Radian */): pos(x,y), vit(500*cos(angle),500*sin(angle)), forme(sf::Quads, 4)
{
    forme[0].position = sf::Vector2f(pos.x-2,pos.y-2);
    forme[1].position = sf::Vector2f(pos.x+2,pos.y-2);
    forme[2].position = sf::Vector2f(pos.x+2,pos.y+2);
    forme[3].position = sf::Vector2f(pos.x-2,pos.y+2);

    forme[0].color = sf::Color::White;
    forme[1].color = sf::Color::White;
    forme[2].color = sf::Color::White;
    forme[3].color = sf::Color::White;
}

void Munition::update(sf::Time deltaTime)
{
    if(!dead) {
        pos += vit * deltaTime.asSeconds();
        render();

        if(pos.x < 0 || pos.x > SIZE_SCREEN_W || pos.y < 0  || pos.y > SIZE_SCREEN_H) { dead = true; }
    }
}

void Munition::render(void)
{
    forme[0].position = sf::Vector2f(pos.x-2,pos.y-2);
    forme[1].position = sf::Vector2f(pos.x+2,pos.y-2);
    forme[2].position = sf::Vector2f(pos.x+2,pos.y+2);
    forme[3].position = sf::Vector2f(pos.x-2,pos.y+2);
}

void Munition::draw(sf::RenderWindow& target)
{
    target.draw(forme);
}

Munition::~Munition()
{
    
}