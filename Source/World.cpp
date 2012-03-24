#include "World.h"

void World::Init()
{
    m_window.Create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Deathliar");
    m_window.SetFramerateLimit(30);

    m_bGameOn = true;

    m_player.SetSprite("Media/Player.png");
}

void World::Update()
{
    sf::Event event;
    while(m_window.GetEvent(event))
    {
        m_player.HandleEvents(event);
        if(event.Type == sf::Event::Closed)
        {
            m_bGameOn = false;
        }
        if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape)
        {
            m_bGameOn = false;
        }
    }
        
    m_window.Clear(sf::Color(255, 255, 255));    
    m_player.Draw(GetFrameTime());
    m_window.Display();
}

void World::Destroy()
{
}