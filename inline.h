/** Auteur: Maxime HAVGOUDOUKIAN
 *  
 *  Nom Projet: Asteroid 
 * 
 *  Date de création: 09/04/2021
 *  Dernière modification: 09/04/2021
 *  
**/

#ifndef INLINE_H_INCLUDED
#define INLINE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "CONSTANTES.hpp"

/**
 *  @brief Renvoie un flotant pseudo-aléatoirement
 * 
 *  @param Min: Borne inférieur de la sélection
 *  @param Max: Borne supérieur de la sélection
 **/
inline float randomf(float Min, float Max) // Renvoie un nombre entier dans l'intervalle [Min;Max]
{
    float offset=0;
    if(abs(Min) > 0) { offset = Min; }
    float res = float(rand())/float(RAND_MAX) * (Max+1 + Min*(-1)) ;
    return res + offset;
}

/**
 *  @brief Renvoie un entier pseudo-aléatoirement
 * 
 *  @param Min: Borne inférieur de la sélection
 *  @param Max: Borne supérieur de la sélection
 **/
inline int randomi(int Min, int Max) // Renvoie un nombre entier dans l'intervalle [Min;Max]
{
    int offset=0;
    if(abs(Min) > 0) { offset = Min; }
    int res = float(rand())/float(RAND_MAX) * (Max+1 + Min*(-1));
    return res + offset;
}

/**
 *  @brief Renvoie l'angle entre l'axe formé avec les deux points et l'axe horizontal
 * 
 *  @param origine: Point d'origine du vecteur de l'axe
 *  @param point: Point directeur du vecteur de l'axe
 * 
 *  @return Angle en RADIANS
 **/
inline float findAngle(const sf::Vector2f origine, const sf::Vector2f point)
{
    sf::Vector2f tempVector = sf::Vector2f(point.x - origine.x, point.y - origine.y);
    float angle =0;

    if(tempVector.x > 0 ) { 
        angle = atan(-tempVector.y / tempVector.x);
        if(angle < 0) { angle = 2*PI + angle; }
    }
    else if(tempVector.x < 0 ) { angle = atan(-tempVector.y / tempVector.x) + PI; }
    else { angle = atan(tempVector.y / tempVector.x); }

    return angle;
}

/**
 *  @brief Effectue la rotation d'un point autour d'un centre
 * 
 *  @param angleSupp: Angle de rotation souhaité (en Radian)
 *  @param origine: Point d'origine
 *  @param point: Point subissant la rotation
 **/
inline void rotationPts(const float angleSupp, const sf::Vector2f origine, sf::Vector2f& point) // rotation dans le sens horaire d'un point
{
    float angle = findAngle(origine, point); // En radian
    float normeVect = sqrtf((point.x - origine.x)*(point.x - origine.x) + (point.y - origine.y)*(point.y - origine.y));

    angle += angleSupp;

    //changement de la position du point
    point.x = normeVect * cos(angle) + origine.x;
    point.y = /* y est inversé dans le repère global */ -normeVect * sin(angle) + origine.y;
}

#endif // INLINE_H_INCLUDED
