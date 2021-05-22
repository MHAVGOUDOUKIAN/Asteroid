/** Auteur: Maxime HAVGOUDOUKIAN
 *
 *  Nom Projet: Asteroid
 *
 *  Date de création: 09/04/2021
 *  Dernière modification: 12/04/2021
 *
 *  C'est la classe principale permettant de générer des particules à l'écran.
 *  C'est une version qui peut encore être optimisée.
 * 
 *  Créer et utiliser un générateur de particules dans un programme:
 *      1 - Déclarer le générateur puis l'initialiser avec une position
 *      2 - Appeler la méthode update(deltaTime) à chaque frame pour mettre à jour le générateur et ses particules
 *      3 - Appeler la méthode draw() pour afficher les particules que contient le générateur
 * 
 *  NB: Le générateur doit se trouver dans une boucle pour fonctionner correctement; il prend en compte le temps écoulé
 *  entre chaque frame
 *
**/

#ifndef PARTICULEGENERATOR_HPP_INCLUDED
#define PARTICULEGENERATOR_HPP_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "inline.h"
#include "Particule.hpp"

template <typename type>
class ParticuleGenerator 
{
    public:
        ParticuleGenerator();
        ParticuleGenerator(const float X, const float Y);
        ~ParticuleGenerator();

        void add(const float X, const float Y); // génère une particule aux positions de la souris
        void add(); // génère une particule aux positions du générateur

        void emit(sf::Time deltaTime); // génère une particule à chaque intervalle de temps "particulePerSecond"
        void update(sf::Time deltaTime);
        void draw(sf::RenderWindow& window);

        size_t size(void) const { return lParticules.size(); }

        void setPosition(const float X, const float Y) { pos.x = X; pos.y = Y; }
        void setPosition(sf::Vector2f& newPos) { pos = newPos; }
        sf::Vector2f getPosition(void) { return pos; }
        void start(void);
        void stop(void);
        void enableDuration(const bool boolean) { EnableDuration = boolean; lifeTime =0; timeLastParticuleAdded=0; };
        bool isWorking(void) const { return working; };
        void setDuration(const float time) { duration = time; } // Modifie la durée de vie du générateur
        void setParticulePerSecond(const int cadence) { particulePerSecond = cadence; }
        float getParticulePerSecond(void) { return particulePerSecond; }
        void setLifeTimeParticule(const float value) { lifeTimeParticule = value; }
        float getLifeTimeParticule(void) { return lifeTimeParticule; }

    private:
        std::vector<type*> lParticules;
        sf::Vector2f pos;
        bool working, EnableDuration; // Indique que le générateur est en cours d'utilisation / Indique que le générateur à une durée de fonctionnement
        float duration, lifeTime; // Durée de vie du générateur
        float particulePerSecond; // Pas de limitation pour générer des particules mais attention aux performances
        float timeLastParticuleAdded; /* Utile uniquement pour emit() // Le nombre de particule max que peut fournir un générateur par seconde dépend des performances du système // 0 => Démarrage du générateur retardé de 'particulePerSecond', toujours initialiser à 1 pour un démarrage direct mais augmente particulePerSecond par 1 */
        float lifeTimeParticule; // Temps de vie des particules
};

template <typename type>
ParticuleGenerator<type>::ParticuleGenerator() : pos(sf::Vector2f(0,0)), working(false), EnableDuration(false), duration(2.f),
lifeTime(0), particulePerSecond(300), timeLastParticuleAdded(0), lifeTimeParticule(0.5f) {}

template <typename type>
ParticuleGenerator<type>::ParticuleGenerator(const float X, const float Y): pos(sf::Vector2f(X,Y)), working(false), EnableDuration(false),
duration(2.f), lifeTime(0), particulePerSecond(300), timeLastParticuleAdded(0), lifeTimeParticule(0.5f) {}

template <typename type>
void ParticuleGenerator<type>::update(sf::Time deltaTime)
{
    lifeTime += deltaTime.asSeconds();

    if(isWorking()) { emit(deltaTime); }

    if(EnableDuration && lifeTime > duration) {
        stop();
        lifeTime = 0;
    }

    for(int i=0; i < int(lParticules.size()); i++) {
        if(!lParticules[i]->isDead()) {
            lParticules[i]->update(deltaTime);
        }
        else {
            delete lParticules[i];
            lParticules.erase(lParticules.begin()+i);
            i--;
        }
    }
}

template <typename type>
void ParticuleGenerator<type>::add(const float X, const float Y)
{
    lParticules.push_back(new type(sf::Mouse::getPosition().x + this->pos.x ,sf::Mouse::getPosition().y + this->pos.y, lifeTimeParticule));
    lParticules[lParticules.size()-1]->launch(lParticules[lParticules.size()-1]->getPosition().x, lParticules[lParticules.size()-1]->getPosition().y, randomf(-700,700), randomf(-1000,1000));
}

template <typename type>
void ParticuleGenerator<type>::add()
{
    lParticules.push_back(new type(this->pos.x ,this->pos.y, lifeTimeParticule));
    lParticules[lParticules.size()-1]->launch(lParticules[lParticules.size()-1]->getPosition().x, lParticules[lParticules.size()-1]->getPosition().y, randomf(-700,700), randomf(-1000,1000));
}

template <typename type>
void ParticuleGenerator<type>::draw(sf::RenderWindow& window)
{
    for(int i=0; i < int(lParticules.size()) ; i++) {
        lParticules[i]->draw(window);
    }
}

template <typename type>
void ParticuleGenerator<type>::emit(sf::Time deltaTime)
{
    timeLastParticuleAdded = timeLastParticuleAdded + deltaTime.asSeconds() * (particulePerSecond); // On calcule le temps qu'il s'est écoulé depuis la dernière update et donc le nombre d'image qui doit être affichées pour respecter la cadence particulePerSecond
    if(timeLastParticuleAdded >= 1) // Si on doit ajouter au moins une particule;;
    {
        for(int i=0; i < int(timeLastParticuleAdded); i++) // On ajoute le bon nombre de particules
        {
            add();
        }
        timeLastParticuleAdded -= int(timeLastParticuleAdded); // On retire le nombre de particules retirées du compteur
    }
}

template <typename type>
void ParticuleGenerator<type>::start(void)
{
    if(!isWorking()) {
        working = true;
        lifeTime=0;
        timeLastParticuleAdded=0;
    }
}

template <typename type>
void ParticuleGenerator<type>::stop(void)
{
    if(isWorking()) {
        working = false;
        lifeTime=0;
        timeLastParticuleAdded=0;
    }
}

template <typename type>
ParticuleGenerator<type>::~ParticuleGenerator() {}

#endif // PARTICULEGENERATOR_HPP_INCLUDED
