/** Auteur: Maxime HAVGOUDOUKIAN
 *
 *  Nom Projet: Asteroid
 *
 *  Date de création: 09/04/2021
 *  Dernière modification: 12/04/2021
 *
 *  Dans ce fichier se trouve toutes les particules que le générateur va pouvoir générer
 *  Pour ce faire il suffit de choisir la particule que va devoir utiliser le générateur
 *  lors de sa déclaration grâce à la généricité : ParticuleGenerateur< ma_Particule > mon_Generateur;
 * 
 *  Chaque type de particule est en fait une instance d'une classe qui: 
 *      - dérive d'une classe virtuelle pure 'Particule'
 *      - décrit les caractéristiques et le comportement des particules
 * 
 *  La construction actuelle du générateur ne permet pas aux particules d'interagir avec l'environnement
 *  extérieur (autres objets, souris, écran, etc..); elles restent fidèles au comportement de base décrit
 *  dans leur classe d'origine.
 * 
 *  Pour créer une nouvelle classe de particules, il faut au minimum la faire dériver de 'Particule' et redéfinir
 *  les cinq méthodes virtuelles pures de celle-ci en fonction du comportement de la particule : 
 *      - update(), launch(), draw(), processPhysics() et processCollision().
 *  Vous pouvez ensuite directement utiliser cette nouvelle classe de particule dans le générateur;
 * 
**/

#ifndef PARTICULE_HPP_INCLUDED
#define PARTICULE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "inline.h"

    //////////////////////////////////////////////////////////////
    ////////////// Particule de base /////////////////////////////  ( NE DOIS PAS ÊTRE UTILISÉE ! )
    //////////////////////////////////////////////////////////////

class Particule // Attributs et méthodes de base d'une particule
{
    public:
        Particule();
        Particule(const float X,const float Y, sf::PrimitiveType type, std::size_t nb_vertex); // Temps de vie de base
        Particule(const float X,const float Y, sf::PrimitiveType type, std::size_t nb_vertex, float dureeVie); // Temps de vie de base au choix
        virtual ~Particule();

        virtual void update(const sf::Time& deltaTime) = 0;
        virtual void launch(const float X, const float Y, const float vit_X, const float vit_Y) = 0; // On met un jour la vitesse et les coords de la particule
        virtual void draw(sf::RenderWindow& window) = 0; // Modifie la table de vertex pour les nouvelles position et autres..
        virtual void processPhysics(void) = 0;
        virtual void processCollision(void) = 0;

        bool isDead(void) const {return m_isDead; }
        sf::Vector2f& getPosition(void) { return m_pos; }
        sf::Vector2f& getVitesse(void) { return m_vit; }
        float getLifeTimeMaxParticule(void) { return m_lifeTimeMax; }
        void setLifeTimeMaxParticule(const float value) { m_lifeTimeMax = value; }

    protected:
        bool m_isDead;
        sf::Vector2f m_pos, m_vit;
        float m_lifeTime, m_lifeTimeMax; // m_lifeTime n'est pas utile pour les utilisateurs
        sf::VertexArray m_forme;
};

    //////////////////////////////////////////////////////////////
    ////////////// Particule Trail ///////////////////////////////
    //////////////////////////////////////////////////////////////

class Particule_Trail : public Particule
{
    public:
        Particule_Trail();
        Particule_Trail(const float X,const float Y);
        Particule_Trail(const float X,const float Y, const float dureeVie);
        virtual ~Particule_Trail();

        virtual void update(const sf::Time& deltaTime);
        virtual void launch(const float X, const float Y, const float vit_X, const float vit_Y);
        virtual void draw(sf::RenderWindow& window);
        virtual void processPhysics(void) {} // Pas de physique, les particules restent sur place
        virtual void processCollision(void) {} // Pas de collisions pour cette particule, on ne fait rien

    protected:
        float m_taille;
        sf::Color m_color;
};

    //////////////////////////////////////////////////////////////
    ////////////// Particule Score ///////////////////////////////
    //////////////////////////////////////////////////////////////

class Particule_Score : public Particule
{
    public:
        Particule_Score();
        Particule_Score(const float X,const float Y);
        Particule_Score(const float X,const float Y, const float dureeVie);
        virtual ~Particule_Score();

        virtual void update(const sf::Time& deltaTime);
        virtual void launch(const float X, const float Y, const float vit_X, const float vit_Y);
        virtual void draw(sf::RenderWindow& window);
        virtual void processPhysics(void) {} // Pas de physique, les particules restent sur place
        virtual void processCollision(void) {} // Pas de collisions pour cette particule, on ne fait rien

    protected:
        float m_taille;
        sf::Color m_color;

        sf::Font font;
        sf::Text texte;
};

   //////////////////////////////////////////////////////////////
    ////////////// Particule Dot ////////////////////////////////
    //////////////////////////////////////////////////////////////

class Particule_Dot : public Particule
{
    public:
        Particule_Dot();
        Particule_Dot(const float X,const float Y);
        Particule_Dot(const float X,const float Y, const float dureeVie);
        virtual ~Particule_Dot();

        virtual void update(const sf::Time& deltaTime);
        virtual void launch(const float X, const float Y, const float vit_X, const float vit_Y);
        virtual void draw(sf::RenderWindow& window);
        virtual void processPhysics(void);
        virtual void processCollision(void) {} // Pas de collisions pour cette particule

    protected:
        float m_taille;
        sf::Color m_color;
};

#endif // PARTICULE_HPP_INCLUDED