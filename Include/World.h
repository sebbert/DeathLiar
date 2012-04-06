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
#include "ParamFile.h"
#include "Camera.h"
#include "LevelEditor.h"

class World
{
public:
    ~World();

    void Init();

    void Update();

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

    ParamFile &GetParams()
    {
        return m_params;
    }

    Vec2D &GetCameraPos()
    {
        return m_camera.m_position;
    }

    Vec2D &GetWindowCenter()
    {
        return m_halfWin;
    }

    bool IsInLevelEditor()
    {
        return m_bLevelEditor;
    }

    /**
     * Checks if point is inside the boundary of the level.
     * @return True if inside, and false if not.
     */
    bool IsInLevel(const Vec2D &point);

    Camera m_camera;            ///< Camera, which alter all the objects in the scene.
private:
    World() {}
    World(const World&) {}
    World operator =(const World&) {}

    LevelEditor m_levelEditor;

    Player m_player;            ///< User controlled entity.
    sf::RenderWindow m_window;  ///< Handle the window.
    Level m_level;              ///< Game level.

    ParamFile m_params;         ///< Parameters set in a file.

    Vec2D m_halfWin;            ///< Half width and heigt of window. In other words center.

    bool m_bSingleFrame;        ///< Single frame application.
    bool m_bGameOn;             ///< True if game should run.
    bool m_bPaused;             ///< True if game is paused.
    bool m_bLevelEditor;        ///< Start up level editor.
};

#define gWorld World::Instance()
#define gWindow World::Instance().GetWindow()

#endif