/** Auteur: Maxime HAVGOUDOUKIAN
 *  
 *  Nom Projet: Asteroid 
 * 
 *  Date de création: 09/04/2021
 *  Dernière modification: 09/04/2021
 *  
**/

#include <iostream>
#include "Engine.hpp"
#include "CONSTANTES.hpp"

Engine::Engine(): m_window(sf::VideoMode(SIZE_SCREEN_W,SIZE_SCREEN_H), "Ma fenetre", FLAGS), j1(300,300)
{
    srand(std::chrono::steady_clock::now().time_since_epoch().count());

    if(!Buff1.loadFromFile("shoot.wav"))
    {
        std::cout << "Fichier son introuvable" << std::endl;
    }
    
    if(!Buff2.loadFromFile("explosion.wav"))
    {
        std::cout << "Fichier son introuvable" << std::endl;
    }

    if(!Buff3.loadFromFile("fusee.ogg"))
    {
        std::cout << "Fichier son introuvable" << std::endl;
    }

    s_shoot.setBuffer(Buff1);
    s_shoot.setVolume(35);
    s_explosion.setBuffer(Buff2);
    s_fusee.setBuffer(Buff3);
    s_fusee.setVolume(65);

    genPartGlobl.setLifeTimeParticule(1.f);

    TimePerFrame = sf::seconds(1.f/FPS);
    m_window.setVerticalSyncEnabled(false);
    m_window.setTitle("Asteroid");
    m_window.setMouseCursorVisible(true);
    
    reset();

    if(!m_fontGame.loadFromFile("AldotheApache.ttf")) {
        std::cout << "Erreur: Impossible de charger la police" << std::endl;
    }

    if(!m_fontScore.loadFromFile("AldotheApache.ttf")) {
        std::cout << "Erreur: Impossible de charger la police" << std::endl;
    }

    m_textGame.setFont(m_fontGame);
    m_textGame.setCharacterSize(64);
    m_textGame.setFillColor(sf::Color::Red);
    m_textGame.setStyle(sf::Text::Regular);
    m_textGame.setString("GAME OVER");
    m_textGame.setPosition(SIZE_SCREEN_W/2 - m_textGame.getLocalBounds().width/2, SIZE_SCREEN_H/2 - m_textGame.getLocalBounds().height/2);

    m_textScore.setFont(m_fontScore);
    m_textScore.setCharacterSize(32);
    m_textScore.setFillColor(sf::Color::Yellow);
    m_textScore.setStyle(sf::Text::Regular);
    m_textScore.setString(std::to_string(score));
    m_textScore.setPosition(10,10);
}

void Engine::reset()
{
    j1.pos.x = SIZE_SCREEN_W/2;
    j1.pos.y = SIZE_SCREEN_H/2;

    score = 0;

    j1.alive=true;
    j1.vit = sf::Vector2f(0,0);
    j1.angle = 0;

    l_asteroid.clear();
    l_balle.clear();

    m_textGame.setFillColor(sf::Color::Red);
    m_textGame.setString("GAME OVER");

    l_asteroid.push_back({randomf(100, SIZE_SCREEN_W-100), 150, randomf(70, 100)});
    l_asteroid.push_back({randomf(100, SIZE_SCREEN_W-100), SIZE_SCREEN_W-150, randomf(70, 100)});
    l_asteroid.push_back({150, randomf(100, SIZE_SCREEN_W-100), randomf(70, 100)});
    l_asteroid.push_back({SIZE_SCREEN_W-150, randomf(100, SIZE_SCREEN_W-100), randomf(70, 100)});
    l_asteroid.push_back({randomf(100, SIZE_SCREEN_W-100), 100, randomf(70, 100)});
}

void Engine::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (m_window.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            processEvents();
            timeSinceLastUpdate -= TimePerFrame;
            update(TimePerFrame);
        }
        render();
    }
}

void Engine::processEvents(void)
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;

            case sf::Event::KeyPressed:
                handleKeyInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handleKeyInput(event.key.code, false);
                break;

            case sf::Event::MouseButtonPressed:
                handleMouseInput(event.mouseButton.button, true);
                break;

            case sf::Event::MouseButtonReleased:
                handleMouseInput(event.mouseButton.button, false);
                break;
        }
    }
}

void Engine::handleKeyInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::Escape) { this-> Echap = isPressed; }
    if(key == sf::Keyboard::Left) {
        this-> Left = isPressed;
        if(!isPressed) { this->LeftPressed=false; }
    }
    if(key == sf::Keyboard::Right) {
        this-> Right = isPressed;
        if(!isPressed) { this->RightPressed=false; }
    }
    if(key == sf::Keyboard::Down) {
        this-> Down = isPressed;
        if(!isPressed) { this->DownPressed=false; }
    }
    if(key == sf::Keyboard::Up) {
        this-> Up = isPressed;
        if(!isPressed) { this->UpPressed=false; }
    }
    if(key == sf::Keyboard::Space) {
        this-> Space = isPressed;
        if(!isPressed) { this->SpacePressed=false; }
    }
    if(key == sf::Keyboard::Z) {
        this-> Z = isPressed;
    }
    if(key == sf::Keyboard::Q) {
        this-> Q = isPressed;
    }
    if(key == sf::Keyboard::D) {
        this-> D = isPressed;
    }
    if(key == sf::Keyboard::M) {
        this-> M = isPressed;
        if(!isPressed) { this->MPressed=false; }
    }
    if(key == sf::Keyboard::P) {
        this-> P = isPressed;
        if(!isPressed) { this->PPressed=false; }
    }
}

void Engine::handleMouseInput(sf::Mouse::Button mouse, bool isPressed)
{
    if(mouse == sf::Mouse::Left) { this-> MouseL = isPressed; }
    if(mouse == sf::Mouse::Right) {
        this-> MouseR = isPressed;
        if(!isPressed) { this->MouseRPressed=false; }
    }
}

void Engine::update(sf::Time deltaTime)
{
    //////////////////////////////////////////////////////////////
    ////////////// Réponse aux inputs ////////////////////////////
    //////////////////////////////////////////////////////////////

    if(j1.alive)
    {
        if(Echap) { m_window.close(); }
        if(MouseL) { }
        if(MouseR && !MouseRPressed) {}
        if(Left || Q) { j1.rotationL(deltaTime); }
        if(Right || D) { j1.rotationR(deltaTime); }
        if(Up || Z) { 
            j1.move(deltaTime);
            
            if(s_fusee.getStatus() != sf::SoundSource::Playing) { 
                s_fusee.play();
                s_fusee.setLoop(true);
            }
        } else { s_fusee.stop(); } 
        if(Down) {  }
        if(Space && !SpacePressed) { 
            l_balle.push_back(Munition(j1.forme[1].position.x,j1.forme[1].position.y, -j1.angle));
            s_shoot.play();
            SpacePressed=true;
        }
        if(M  && !MPressed) { 
            mute = !mute; 
            MPressed=true;

            if(mute) {
                s_shoot.setVolume(0);
                s_explosion.setVolume(0);
                s_fusee.setVolume(0);
            } else {
                s_shoot.setVolume(35);
                s_explosion.setVolume(100);
                s_fusee.setVolume(65);
            }
        }
        if(P && !PPressed) { 
            PPressed=true;
            sc++;
            if(sc > 3) { sc = 0; }
        }
    }
    else
    {
        s_fusee.stop();
        if(Echap) { m_window.close(); }
        if(Space && !SpacePressed) { 
            reset();
            SpacePressed=true;
        }
        if(M  && !MPressed) { 
            mute = !mute; 
            MPressed=true;

            if(mute) {
                s_shoot.setVolume(0);
                s_explosion.setVolume(0);
                s_fusee.setVolume(0);
            } else {
                s_shoot.setVolume(35);
                s_explosion.setVolume(100);
                s_fusee.setVolume(65);
            }
        }
    }

    //////////////////////////////////////////////////
    ////////////// Update ////////////////////////////
    //////////////////////////////////////////////////

    j1.update(deltaTime);

    for(size_t i=0; i < l_asteroid.size(); i++)
    {
        l_asteroid[i].update(deltaTime);
        if(overlapping(j1.forme,l_asteroid[i].forme) && overlapping(l_asteroid[i].forme,j1.forme))
        {
            j1.alive=false;
        }
    }

    std::vector<Obstacle> new_Aster;
    for(size_t i=0; i < l_balle.size(); i++)
    {
        l_balle[i].update(deltaTime);
        for(size_t j=0; j < l_asteroid.size(); j++)
        {
            if(!l_asteroid[j].dead) {
                if(overlapping(l_balle[i].forme,l_asteroid[j].forme) && overlapping(l_asteroid[j].forme,l_balle[i].forme))
                {
                    l_balle[i].dead=true;
                    l_asteroid[j].dead=true;
                    s_explosion.play();

                    genPartGlobl.setPosition(l_asteroid[j].pos.x, l_asteroid[j].pos.y);
                    genPartGlobl.add();

                    score += 100;

                    if(l_asteroid[j].rayon > 25) {
                        new_Aster.push_back(Obstacle(l_asteroid[j].pos.x + randomf(-20, 20), l_asteroid[j].pos.y + randomf(-20, 20), l_asteroid[j].rayon * 0.6));
                        new_Aster.push_back(Obstacle(l_asteroid[j].pos.x + randomf(-20, 20), l_asteroid[j].pos.y + randomf(-20, 20), l_asteroid[j].rayon * 0.6));
                        if(l_asteroid[j].rayon < 40) {
                            new_Aster.push_back(Obstacle(l_asteroid[j].pos.x + randomf(-20, 20), l_asteroid[j].pos.y + randomf(-20, 20), l_asteroid[j].rayon * 0.6));
                        }
                    }
                }
            }
        }

        if(l_balle[i].dead)
        {
            l_balle.erase(l_balle.begin()+i);
            i--;
        }
    }

    genPartGlobl.update(deltaTime);
    m_textScore.setString(std::to_string(score));

    for(size_t i=0; i < new_Aster.size(); i++)
    {
        l_asteroid.push_back(new_Aster[i]);
    }

    for(size_t i=0; i < l_asteroid.size(); i++)
    {
        if(l_asteroid[i].dead)
        {
            l_asteroid.erase(l_asteroid.begin()+i);
            i--;
        }
    }

    if(l_asteroid.empty())
    {
            m_textGame.setFillColor(sf::Color::Green);
            m_textGame.setString("VICTOIRE !");
            j1.alive = false;
    }
}

void Engine::render(void)
{
    m_window.clear();
    
    for(size_t i=0; i < l_asteroid.size(); i++) { l_asteroid[i].draw(m_window); }
    for(size_t i=0; i < l_balle.size(); i++) { l_balle[i].draw(m_window); }
    
    if(sc != 1 && sc != 3) { genPartGlobl.draw(m_window); }
    if(sc != 2 && sc != 3) { m_window.draw(m_textScore); }
    
    if(j1.alive) {j1.draw(m_window);}
    else{m_window.draw(m_textGame);}

    m_window.display();
}

bool Engine::overlapping(sf::VertexArray &j1, sf::VertexArray &j2)
{
    
    for(size_t i=0; i < j1.getVertexCount(); i++) {
        int j = (i+1)%j1.getVertexCount();
        sf::Vector2f axeProjection = sf::Vector2f(-(j1[j].position.y - j1[i].position.y) ,j1[j].position.x - j1[i].position.x);

        float minf1 = 1000000, maxf1 = -1000000;
        for(size_t e=0; e < j1.getVertexCount(); e++) {
            float proj = j1[e].position.x * axeProjection.x + j1[e].position.y * axeProjection.y;
            minf1 = std::min(minf1, proj);
            maxf1 = std::max(maxf1, proj);
        }

        float minf2 = 1000000, maxf2 = -1000000;
        for(size_t e=0; e < j2.getVertexCount(); e++) {
            float proj = j2[e].position.x * axeProjection.x + j2[e].position.y * axeProjection.y;
            minf2 = std::min(minf2, proj);
            maxf2 = std::max(maxf2, proj);
        }

        if(!(maxf2 > minf1 && maxf1> minf2)) { return false; }
    }
    return true;
}

Engine::~Engine()
{}