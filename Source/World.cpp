/**
* This file is part of
* 
* 8888888b.                    888    888      888      d8b                  
* 888  "Y88b                   888    888      888      Y8P                  
* 888    888                   888    888      888                           
* 888    888  .d88b.   8888b.  888888 88888b.  888      888  8888b.  888d888 
* 888    888 d8P  Y8b     "88b 888    888 "88b 888      888     "88b 888P"   
* 888    888 88888888 .d888888 888    888  888 888      888 .d888888 888     
* 888  .d88P Y8b.     888  888 Y88b.  888  888 888      888 888  888 888     
* 8888888P"   "Y8888  "Y888888  "Y888 888  888 88888888 888 "Y888888 888   
* 
* Copyright © 2012 Emil Sandstø, Sebastian Reinhard
* 
*/

#include "World.h"

void World::Init()
{
    m_window.Create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Deathliar");
    m_window.SetFramerateLimit(30);

    m_bGameOn = true;

    m_level.Init();

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
    
    m_level.Draw();
    m_player.Draw(GetFrameTime());
    
    m_window.Display();
}

void World::Destroy()
{
}