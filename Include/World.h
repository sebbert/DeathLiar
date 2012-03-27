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

#ifndef WORLD_H
#define WORLD_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "MathUtil.h"
#include "Player.h"
#include "Level.h"
#include "Enemy.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class World
{
public:
    void Init();

    void Update();

    void Destroy();

    static World &Instance()
    {
        static World m_instance;
        return m_instance;
    }

    sf::RenderWindow *GetWindow()
    {
        return &m_window;
    }

    Real GetFrameTime()
    {
        //return (Real)m_window.GetFrameTime();
        return (Real)0.03333;
    }

    bool GameOn()
    {
        return m_bGameOn;
    }

    Player& GetPlayer()
    {
        return m_player;
    }

    Level &GetLevel()
    {
        return m_level;
    }

    Vec2D GetLevelPos()
    {
        Vec2D levelPos = m_lastLevelPos - m_level.m_position.Opposite();
        m_lastLevelPos = m_level.m_position.Opposite();
        return levelPos;
    }
private:
    World() {}
    World(const World&) {}
    World operator =(const World&) {}

    Enemy m_enemy;              ///< AI driven enemy.
    Player m_player;            ///< User controlled entity.
    sf::RenderWindow m_window;  ///< Handle the window.
    Level m_level;              ///< Game level.
    Vec2D m_lastLevelPos;

    bool m_bSingleFrame;        ///< Single frame application.
    bool m_bGameOn;             ///< True if game should run.
    bool m_bPaused;             ///< True if game is paused.
};

#define gWorld World::Instance()
#define gWindow World::Instance().GetWindow()

#endif