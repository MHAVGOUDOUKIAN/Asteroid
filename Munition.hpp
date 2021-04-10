/** Auteur: Maxime HAVGOUDOUKIAN
 *  
 *  Nom Projet: Asteroid 
 * 
 *  Date de création: 09/04/2021
 *  Dernière modification: 09/04/2021
 *  
**/

#ifndef MUNITION_HPP_INCLUDED
#define MUNITION_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "CONSTANTES.hpp"
#include <cmath>

class Munition
{
    public:
        Munition(const float x, const float y, const float angle);
        ~Munition();

        void update(sf::Time deltaTime);
        void render(void);
        void draw( sf::RenderWindow& target);

    public:
        sf::Vector2f pos, vit;
        bool dead = false;
        sf::VertexArray forme;
};

#endif // MUNITION_HPP_INCLUDED
