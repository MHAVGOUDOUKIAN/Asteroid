/** Auteur: Maxime HAVGOUDOUKIAN
 *  
 *  Nom Projet: Asteroid 
 * 
 *  Date de création: 09/04/2021
 *  Dernière modification: 09/04/2021
 *  
**/

#include "Obstacle.hpp"
#include <cmath>

Obstacle::Obstacle(const float x, const float y): dir(1,0), pos(x,y), vit(50), rayon(30), angle(0), vitAngle(180), forme(sf::LineStrip, 10)
{
    srand(std::chrono::steady_clock::now().time_since_epoch().count());

    angle= randomf(0,360) * PI/180;

    dir.x = cos(angle);
    dir.y = sin(angle);

    rayonMax = -10000;
    rayon = randomi(10, 100);

    vit = 1/rayon * 4000;
    vitAngle = 1/rayon * 680;

    for(size_t i=0; i < forme.getVertexCount()-1; i++)
    {
        float rayonPts = randomf(0,20) + rayon;
        forme[i].position = sf::Vector2f(rayonPts*cos(360 * i/(forme.getVertexCount()-1) * PI/180)+pos.x, rayonPts*sin(360 * i/(forme.getVertexCount()-1)* PI/180)+pos.y);
        forme[i].color = sf::Color::White;
        rayonInit.push_back(rayonPts);

        if(rayonMax < rayonPts) { rayonMax = rayonPts; }
    }
    forme[forme.getVertexCount()-1].position.x = forme[0].position.x;
    forme[forme.getVertexCount()-1].position.y = forme[0].position.y;
    rayonInit.push_back(rayonInit[0]);
}

Obstacle::Obstacle(const float x, const float y, const float radius): dir(1,0), pos(x,y), vit(50), rayon(radius), angle(0), vitAngle(180), forme(sf::LineStrip, 10)
{
    srand(std::chrono::steady_clock::now().time_since_epoch().count());

    angle= randomf(0,360) * PI/180;

    dir.x = cos(angle);
    dir.y = sin(angle);

    rayonMax = -10000;

    vit = 1/rayon * 4000;
    vitAngle = 1/rayon * 680;

    for(size_t i=0; i < forme.getVertexCount()-1; i++)
    {
        float rayonPts = randomf(0,20) + rayon;
        forme[i].position = sf::Vector2f(rayonPts*cos(360 * i/(forme.getVertexCount()-1) * PI/180)+pos.x, rayonPts*sin(360 * i/(forme.getVertexCount()-1)* PI/180)+pos.y);
        forme[i].color = sf::Color::White;
        rayonInit.push_back(rayonPts);

        if(rayonMax < rayonPts) { rayonMax = rayonPts; }
    }
    forme[forme.getVertexCount()-1].position.x = forme[0].position.x;
    forme[forme.getVertexCount()-1].position.y = forme[0].position.y;
    rayonInit.push_back(rayonInit[0]);
}

void Obstacle::update(sf::Time deltaTime)
{
    if(!dead) {    
        pos += dir * vit * deltaTime.asSeconds();
        angle += vitAngle * PI/180 * deltaTime.asSeconds();

        if(pos.x < 0 - rayonMax) {pos.x = SIZE_SCREEN_W + rayonMax;}
        if(pos.x > SIZE_SCREEN_W + rayonMax) {pos.x = 1 - rayonMax;}

        if(pos.y < 0 - rayonMax) {pos.y = SIZE_SCREEN_H + rayonMax;}
        if(pos.y > SIZE_SCREEN_H + rayonMax) {pos.y = 1 - rayonMax;}
    }
    render();
}

void Obstacle::render()
{
    for(size_t i=0; i < forme.getVertexCount(); i++)
    {
        forme[i].position = sf::Vector2f(rayonInit[i]*cos(360 * i/(forme.getVertexCount()-1) * PI/180)+pos.x, rayonInit[i] *sin(360 * i/(forme.getVertexCount()-1)* PI/180)+pos.y);
        rotationPts(angle, pos,forme[i].position);
    }
}

void Obstacle::draw(sf::RenderWindow& target)
{
    render();
    target.draw(forme);
}

Obstacle::~Obstacle()
{

}