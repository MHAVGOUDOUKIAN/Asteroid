/** Auteur: Maxime HAVGOUDOUKIAN
 *  
 *  Nom Projet: Asteroid 
 * 
 *  Date de création: 09/04/2021
 *  Dernière modification: 09/04/2021
 *  
**/

#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Obstacle.hpp"
#include "Munition.hpp"
#include <vector>

class Engine
{
    public:
        Engine();
        ~Engine();

        void run();
        void reset();
        void update(sf::Time deltaTime);
        void processEvents();
        void handleKeyInput(sf::Keyboard::Key key, bool isPressed);
        void handleMouseInput(sf::Mouse::Button mouse, bool isPressed);
        void render();

        bool overlapping(sf::VertexArray &j1, sf::VertexArray &j2);

    public: // Normalement priv�
        bool MouseL=false, MouseR=false, Echap=false, MouseRPressed = false;
        bool Left=false, Right=false, Up=false, Space=false, Down=false, Z=false, Q=false, D=false;
        bool SpacePressed=false, UpPressed=false, DownPressed=false, LeftPressed=false, RightPressed=false;
        sf::RenderWindow m_window;
        sf::Time TimePerFrame;
        Player j1;
        std::vector<Obstacle> l_asteroid;
        std::vector<Munition> l_balle;
        sf::Font m_fontGame;
        sf::Text m_textGame;
};

#endif // ENGINE_HPP_INCLUDED
