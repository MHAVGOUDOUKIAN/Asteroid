#include "Particule.hpp"
#include <cmath>
#include <iostream>
#include "CONSTANTES.hpp"

#define g 10 * 150
#define h 5

    //////////////////////////////////////////////////////////////
    ////////////// Particule de base /////////////////////////////  ( NE DOIS PAS ÊTRE UTILISÉE ! )
    //////////////////////////////////////////////////////////////

Particule::Particule() : m_isDead(false), m_pos(sf::Vector2f(0,0)), m_vit(sf::Vector2f(0,0)), m_lifeTime(0.f), m_lifeTimeMax(0.2f) {}

Particule::Particule(const float X,const float Y, sf::PrimitiveType type, std::size_t nb_vertex) : m_isDead(false), m_pos(sf::Vector2f(X,Y)), m_vit(sf::Vector2f(0,0)),
m_lifeTime(0.f), m_lifeTimeMax(0.2f), m_forme(type, nb_vertex) {}

Particule::Particule(const float X,const float Y, sf::PrimitiveType type, std::size_t nb_vertex, float dureeVie): m_isDead(false), m_pos(sf::Vector2f(X,Y)),
m_vit(sf::Vector2f(0,0)), m_lifeTime(0.f), m_lifeTimeMax(dureeVie), m_forme(type, nb_vertex) {}

Particule::~Particule() {}


    //////////////////////////////////////////////////////////////
    ////////////// Particule Trail ///////////////////////////////
    //////////////////////////////////////////////////////////////

Particule_Trail::Particule_Trail() : Particule(0,0,sf::Quads, 4), m_taille(10) {
    int color = randomi(1,3);

    if(color == 1) { m_color = sf::Color::Red; }
    else if(color == 2) { m_color = sf::Color::Yellow; }
    else if(color == 3) { m_color = sf::Color(255,128,0); }
    
    m_lifeTimeMax = 0.5f;
}

Particule_Trail::Particule_Trail(const float X, const float Y) : Particule(X,Y,sf::Quads, 4), m_taille(10) {
    int color = randomi(1,3);

    if(color == 1) { m_color = sf::Color::Red; }
    else if(color == 2) { m_color = sf::Color::Yellow; }
    else if(color == 3) { m_color = sf::Color(255,128,0); }

    m_lifeTimeMax = 0.5f;
}

Particule_Trail::Particule_Trail(const float X,const float Y, const float dureeVie) : Particule(X,Y,sf::Quads, 4, 0.35), m_taille(10) {
   int color = randomi(1,3);

    if(color == 1) { m_color = sf::Color::Red; }
    else if(color == 2) { m_color = sf::Color::Yellow; }
    else if(color == 3) { m_color = sf::Color(255,128,0); }
}

void Particule_Trail::update(const sf::Time& deltaTime)
{
    m_lifeTime += deltaTime.asSeconds();

    if(m_lifeTime>m_lifeTimeMax) { m_isDead = true; }

    processPhysics();
    processCollision();

    m_forme[0].position = sf::Vector2f(m_pos.x - m_taille * (1-(m_lifeTime/m_lifeTimeMax))/2, m_pos.y - m_taille * (1-(m_lifeTime/m_lifeTimeMax))/2);
    m_forme[1].position = sf::Vector2f(m_pos.x + m_taille * (1-(m_lifeTime/m_lifeTimeMax))/2, m_pos.y - m_taille * (1-(m_lifeTime/m_lifeTimeMax))/2);
    m_forme[2].position = sf::Vector2f(m_pos.x + m_taille * (1-(m_lifeTime/m_lifeTimeMax))/2, m_pos.y + m_taille * (1-(m_lifeTime/m_lifeTimeMax))/2);
    m_forme[3].position = sf::Vector2f(m_pos.x - m_taille * (1-(m_lifeTime/m_lifeTimeMax))/2, m_pos.y + m_taille * (1-(m_lifeTime/m_lifeTimeMax))/2);

    m_forme[0].color = m_color;
    m_forme[1].color = m_color;
    m_forme[2].color = m_color;
    m_forme[3].color = m_color;
}

void Particule_Trail::launch(const float X, const float Y, const float vit_X, const float vit_Y)
{
    m_pos = sf::Vector2f(randomf(X-5, X+5), randomf(Y-5, Y+5));
    m_vit = sf::Vector2f(0,0);
}

void Particule_Trail::draw(sf::RenderWindow& window)
{
    window.draw(m_forme);
}

Particule_Trail::~Particule_Trail() {}