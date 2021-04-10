/** Auteur: Maxime HAVGOUDOUKIAN
 *  
 *  Nom Projet: Asteroid 
 * 
 *  Date de création: 09/04/2021
 *  Dernière modification: 09/04/2021
 *  
**/

#ifndef OBSTACLE_HPP_INCLUDED
#define OBSTACLE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include <vector>
#include <iostream>
#include "inline.h"
#include <cmath>
#include "CONSTANTES.hpp"

class Obstacle
{
    public:
        Obstacle(const float x, const float y); // Pour créer des asteroids
        Obstacle(const float x, const float y, const float radius);
        ~Obstacle();

        void update(sf::Time deltaTime);
        void render(void);
        void draw( sf::RenderWindow& target);

        sf::Vector2f dir, pos;
        float vit, rayon, angle /* en Radian */, vitAngle;

        float rayonMax;
        bool dead=false;

        sf::VertexArray forme;
        std::vector<float> rayonInit;


    private:
};

#endif // OBSTACLE_HPP_INCLUDED
