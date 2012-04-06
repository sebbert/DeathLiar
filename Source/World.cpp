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
#include "Weapon.h"
#include "GameMaster.h"

void World::Init()
{
    m_params.Init();

    m_window.Create(sf::VideoMode(m_params.m_windowWidth, m_params.m_windowHeight, 32), "Deathliar");
    m_window.SetFramerateLimit(30);

    m_halfWin.x = m_params.m_windowWidth * (Real)0.5;
    m_halfWin.y = m_params.m_windowHeight * (Real)0.5;
    m_bGameOn = true;

    m_level.Init("Graveyard");
    gBulletMgr.Init();

    m_player.Init();
    m_player.SetSprite("Media/Player.png");
    m_player.SetHealth(200);

    gGameMaster.Init();
}

void World::Update()
{
    sf::Event event;
    while(m_window.GetEvent(event))
    {
        m_player.HandleEvents(event);
        
        if(m_bLevelEditor)
        {
            m_levelEditor.HandleEvents(event);
        }

        if(event.Type == sf::Event::Closed)
        {
            m_bGameOn = false;
        }
        else if(event.Type == sf::Event::KeyPressed)
        {
            if(event.Key.Code == sf::Key::Escape)
            {
                m_bGameOn = false;
            }
            else if(event.Key.Code == sf::Key::P)
            {
                //Pause game...
                m_bPaused = !m_bPaused;
            }
            else if(event.Key.Code == sf::Key::O && !event.Key.Control)
            {
                //Single frame
                m_bSingleFrame = true;
                m_bPaused = false;
            }
            else if(event.Key.Code == sf::Key::F10)
            {
                if(m_bLevelEditor == false)
                {
                    m_bLevelEditor = true;
                    m_levelEditor.Init();
                }
                else
                {
                    m_bLevelEditor = false;
                    m_levelEditor.Destroy();
                    Init();
                }
            }
        }
    }
    
    if(!m_bPaused)
    {
        m_window.Clear(sf::Color(255, 255, 255));    
    
        m_level.Draw();
        m_player.Draw(GetFrameTime());
        if(!m_bLevelEditor)
        {
            gGameMaster.Update(GetFrameTime());

            gBulletMgr.Update(GetFrameTime());
        }
        else
        {
            m_levelEditor.Draw();
        }

        m_window.Display();

        if(m_bSingleFrame)
        {
            m_bSingleFrame = false;
            m_bPaused = true;
        }
    }
}

bool World::IsInLevel(const Vec2D &point)
{
    if(point.x < 0 || point.x > m_level.m_levelWidth || point.y < 0 || point.y > m_level.m_levelHeight)
    {
        return false;
    }

    return true;
}

World::~World()
{
    m_level.Destroy();
    gGameMaster.Destroy();
    m_levelEditor.Destroy();
}