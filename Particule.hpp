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

#endif // PARTICULE_HPP_INCLUDED