/** Auteur: Maxime HAVGOUDOUKIAN
 *
 *  Nom Projet: Asteroid
 *
 *  Date de création: 09/04/2021
 *  Dernière modification: 09/04/2021
 *
**/

#include "Player.hpp"

Player::Player(const float x, const float y): angle(0), vitAngulaire(360), acc(250), pos(x,y), vit(0,0), forme(sf::Quads, 5)
{
    forme[0].position = sf::Vector2f(pos.x-15,pos.y-5);
    forme[1].position = sf::Vector2f(pos.x+35,pos.y);
    forme[2].position = sf::Vector2f(pos.x-15,pos.y+5);
    forme[3].position = sf::Vector2f(pos.x-5,pos.y);
    forme[4].position = sf::Vector2f(pos.x-13,pos.y);

    forme[0].color = sf::Color::White;
    forme[1].color = sf::Color(121,121,121);
    forme[2].color = sf::Color::White;
    forme[3].color = sf::Color(121,121,121);

    genPart.setPosition(forme[4].position);
    genPart.setLifeTimeParticule(1.f);
    genPart.setParticulePerSecond(50.f);
    genPart.setDuration(0.3f);
    genPart.enableDuration(true);
}

void Player::rotationL(sf::Time deltaTime)
{
    angle += vitAngulaire * PI/180 * deltaTime.asSeconds();
}

void Player::rotationR(sf::Time deltaTime)
{
    angle -= vitAngulaire * PI/180 * deltaTime.asSeconds();
}

void Player::move(sf::Time deltaTime) //
{
    genPart.start();
    vit.x += cos(angle) * acc * deltaTime.asSeconds();
    vit.y += -sin(angle) * acc * deltaTime.asSeconds();
    
}

void Player::update(sf::Time deltaTime)
{
    pos += vit * deltaTime.asSeconds();

    render();
    genPart.update(deltaTime);

    if(pos.x < 0) {pos.x = SIZE_SCREEN_W - 1;}
    if(pos.x > SIZE_SCREEN_W) {pos.x = 1;}

    if(pos.y < 0) {pos.y = SIZE_SCREEN_H - 1;}
    if(pos.y > SIZE_SCREEN_H) {pos.y = 1;}
}

void Player::render(void)
{
    forme[0].position = sf::Vector2f(pos.x-15,pos.y-15);
    forme[1].position = sf::Vector2f(pos.x+35,pos.y);
    forme[2].position = sf::Vector2f(pos.x-15,pos.y+15);
    forme[3].position = sf::Vector2f(pos.x-5,pos.y);
    forme[4].position = sf::Vector2f(pos.x-13,pos.y);

    for(size_t i=0; i < forme.getVertexCount(); i++)
    {
        rotationPts(angle, pos,forme[i].position);
    }

    genPart.setPosition(forme[4].position);
}

void Player::draw(sf::RenderWindow& target)
{
    genPart.draw(target);
    target.draw(forme);
}

Player::~Player() {}
