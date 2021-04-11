/** Auteur: Maxime HAVGOUDOUKIAN
 *  
 *  Nom Projet: Asteroid 
 * 
 *  Date de création: 09/04/2021
 *  Dernière modification: 12/04/2021
 *  
 *  Classe décrivant les caractéristiques du joueur
 * 
 *  La rotation du joueur et même de n'importe quelles formes se fait à l'aide
 *  des méthodes prévues à cette effet dans le fichier 'inline.h'
 * 
 *  Ce qui donne cette effet d'inertie très intéressant dans les déplacement du joueur est simplement la variation PROGRESSIVE
 *  du vecteur vitesse grâce à l'angle du joueur et l'accélération.
 * 
 *  Dans ma première tentative la vecteur vitesse possédait toujours la même norme et était tout de suite dirigé selon
 *  l'angle du joueur, donc lors des déplacement le joueur changait tout de suite de direction
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