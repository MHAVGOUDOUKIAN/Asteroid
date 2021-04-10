/** Auteur: Maxime HAVGOUDOUKIAN
 *  
 *  Nom Projet: Asteroid 
 * 
 *  Date de création: 09/04/2021
 *  Dernière modification: 09/04/2021
 *  
**/

#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <cmath>
#include "inline.h"
#include "CONSTANTES.hpp"
#include <vector>
#include "ParticuleGenerator.hpp"

class Player
{
    public:
        Player(const float x, const float y);
        ~Player();

        void rotationL(sf::Time deltaTime);
        void rotationR(sf::Time deltaTime);
        void move(sf::Time deltaTime);

        void shoot(void);

        void update(sf::Time); // à configurer selon le comportement de l'objet
        void render(void); // Met à jour la table de vertex
        void draw(sf::RenderWindow& target); // Affiche le tout

        float angle, vitAngulaire, acc; // angle en radian
        sf::Vector2f pos, vit;
        sf::VertexArray forme;

        bool alive=true;
        ParticuleGenerator<Particule_Trail> genPart;
        
    private:
};

#endif // PLAYER_HPP_INCLUDED