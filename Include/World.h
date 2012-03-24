/**
* Part of Deathliar
* Copyright (c) Emil Sandstø 2012
*/
#ifndef WORLD_H
#define WORLD_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "MathUtil.h"
#include "Player.h"

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
        return (Real)0.033;
    }

    bool GameOn()
    {
        return m_bGameOn;
    }
private:
    World() {}
    World(const World&) {}
    World operator =(const World&) {}

    Player m_player;///< User controlled entity.
    sf::RenderWindow m_window;///< Handle the window.

    bool m_bGameOn;///< True if game should run.
};

#define gWorld World::Instance()
#define gWindow World::Instance().GetWindow()
#endif