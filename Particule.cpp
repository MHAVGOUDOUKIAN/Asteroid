/** Auteur: Maxime HAVGOUDOUKIAN
 *
 *  Nom Projet: Asteroid
 *
 *  Date de création: 09/04/2021
 *  Dernière modification: 12/04/2021
 *
**/

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

    //////////////////////////////////////////////////////////////
    ////////////// Particule Score ///////////////////////////////
    //////////////////////////////////////////////////////////////

Particule_Score::Particule_Score() : Particule(0,0,sf::Quads, 4), m_taille(10) {
    
    m_color = sf::Color::Yellow;
    m_lifeTimeMax = 0.5f;
    
    if(!font.loadFromFile("AldotheApache.ttf"))
    {
        std::cout << "Impossible de charger la texture des particules" << std::endl;
    }
    texte.setFont(font);
    texte.setCharacterSize(32);
    texte.setFillColor(sf::Color::Yellow);
    texte.setStyle(sf::Text::Regular);
    texte.setString("+100");
    texte.setPosition(SIZE_SCREEN_W/2 - texte.getLocalBounds().width/2, SIZE_SCREEN_H/2 - texte.getLocalBounds().height/2);
}

Particule_Score::Particule_Score(const float X, const float Y) : Particule(X,Y,sf::Quads, 4), m_taille(10) {
    m_color = sf::Color::Yellow;
    m_lifeTimeMax = 0.5f;

    if(!font.loadFromFile("AldotheApache.ttf"))
    {
        std::cout << "Impossible de charger la texture des particules" << std::endl;
    }
    texte.setFont(font);
    texte.setCharacterSize(32);
    texte.setFillColor(sf::Color::Yellow);
    texte.setStyle(sf::Text::Regular);
    texte.setString("+100");
    texte.setPosition(SIZE_SCREEN_W/2 - texte.getLocalBounds().width/2, SIZE_SCREEN_H/2 - texte.getLocalBounds().height/2);
}

Particule_Score::Particule_Score(const float X,const float Y, const float dureeVie) : Particule(X,Y,sf::Quads, 4, dureeVie), m_taille(10) {
    m_color = sf::Color::Yellow;

    if(!font.loadFromFile("AldotheApache.ttf"))
    {
        std::cout << "Impossible de charger la texture des particules" << std::endl;
    }
    texte.setFont(font);
    texte.setCharacterSize(28);
    texte.setFillColor(sf::Color::Yellow);
    texte.setStyle(sf::Text::Regular);
    texte.setString("+100");
    texte.setPosition(m_pos.x - texte.getLocalBounds().width/2, m_pos.y - texte.getLocalBounds().height/2);
}

void Particule_Score::update(const sf::Time& deltaTime)
{
    m_lifeTime += deltaTime.asSeconds();

    if(m_lifeTime>m_lifeTimeMax) { m_isDead = true; }

    processPhysics();
    processCollision();

    texte.setPosition(texte.getPosition().x + m_vit.x * deltaTime.asSeconds(), texte.getPosition().y + m_vit.y * deltaTime.asSeconds());
}

void Particule_Score::launch(const float X, const float Y, const float vit_X, const float vit_Y)
{
    m_pos = sf::Vector2f(X,Y);
    m_vit = sf::Vector2f(0,-100);
}

void Particule_Score::draw(sf::RenderWindow& window)
{
    window.draw(texte);
}

Particule_Score::~Particule_Score() {}  

    //////////////////////////////////////////////////////////////
    ////////////// Particule Dot ////////////////////////////////
    //////////////////////////////////////////////////////////////

Particule_Dot::Particule_Dot() : Particule(0,0,sf::Quads, 4), m_taille(2) {
    m_color = sf::Color::White;
    m_lifeTimeMax = 0.5f;
}

Particule_Dot::Particule_Dot(const float X, const float Y) : Particule(X,Y,sf::Quads, 4), m_taille(2) {
    m_color = sf::Color::White;
    m_lifeTimeMax = 0.5f;
}

Particule_Dot::Particule_Dot(const float X,const float Y, const float dureeVie) : Particule(X,Y,sf::Quads, 4, dureeVie), m_taille(2) {
    m_color = sf::Color::White;
}

void Particule_Dot::update(const sf::Time& deltaTime)
{
    m_lifeTime += deltaTime.asSeconds();

    if(m_lifeTime>m_lifeTimeMax || m_pos.x < 0 || m_pos.x > 1920 || m_pos.y < 0 || m_pos.y > 1080) { m_isDead = true; }

    processPhysics();
    processCollision();

    m_forme[0].position = sf::Vector2f(m_pos.x - m_taille/2, m_pos.y - m_taille/2);
    m_forme[1].position = sf::Vector2f(m_pos.x + m_taille/2, m_pos.y - m_taille/2);
    m_forme[2].position = sf::Vector2f(m_pos.x + m_taille/2, m_pos.y + m_taille/2);
    m_forme[3].position = sf::Vector2f(m_pos.x - m_taille/2, m_pos.y + m_taille/2);

    m_forme[0].color = m_color;
    m_forme[1].color = m_color;
    m_forme[2].color = m_color;
    m_forme[3].color = m_color;
}

void Particule_Dot::processPhysics(void) // Problème de la balle lancée en (x,y) à la vitesse V(v_x,v_y)
{
    m_pos.x += m_vit.x;
    m_pos.y += m_vit.y;
}

void Particule_Dot::launch(const float X, const float Y, const float vit_X, const float vit_Y)
{
    m_pos = sf::Vector2f(X,Y);
    m_vit = sf::Vector2f(randomf(-5.f,5.f),randomf(-5.f,5.f));
}

void Particule_Dot::draw(sf::RenderWindow& window)
{
    window.draw(m_forme);
}

Particule_Dot::~Particule_Dot() {}
