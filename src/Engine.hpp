/** Auteur: Maxime HAVGOUDOUKIAN
 *
 *  Nom Projet: Asteroid
 *
 *  Date de création: 09/04/2021
 *  Dernière modification: 12/04/2021
 *
 *  Contient la boucle principale du jeu
 *
**/

#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.hpp"
#include "Obstacle.hpp"
#include "Munition.hpp"
#include <vector>
#include <chrono>
#include "ParticuleGenerator.hpp"
#include "CONSTANTES.hpp"
#include "inline.h"

class Engine
{
    public:
        Engine();
        ~Engine();

        void run();
        void reset(); // Relance un partie
        void update(sf::Time deltaTime);
        void processEvents();
        void handleKeyInput(sf::Keyboard::Key key, bool isPressed);
        void handleMouseInput(sf::Mouse::Button mouse, bool isPressed);
        void render(); // Partie rendu de l'application

    public: // Normalement privé
        bool MouseL=false, MouseR=false, Echap=false, MouseRPressed = false;
        bool Left=false, Right=false, Up=false, Space=false, Down=false, Z=false, Q=false, D=false, M=false, P=false;
        bool SpacePressed=false, UpPressed=false, DownPressed=false, LeftPressed=false, RightPressed=false, MPressed=false, PPressed=false;

        sf::RenderWindow m_window;
        sf::Time TimePerFrame;
        Player j1;
        short sc=0;
        int score=0;
        std::vector<Obstacle> l_asteroid;
        std::vector<Munition> l_balle;

        sf::Font m_fontGame;
        sf::Text m_textGame;
        sf::Font m_fontScore;
        sf::Text m_textScore;

        ParticuleGenerator<Particule_Score> genPartGlobl;
        ParticuleGenerator<Particule_Dot> genPartGlobl2;

        sf::SoundBuffer Buff1;
        sf::SoundBuffer Buff2;
        sf::SoundBuffer Buff3;
        sf::Sound s_shoot;
        sf::Sound s_explosion;
        sf::Sound s_fusee;
        bool musicOn = false;
        bool mute=false;
};

#endif // ENGINE_HPP_INCLUDED