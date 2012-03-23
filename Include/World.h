/**
* Part of Deathliar
* Copyright (c) Emil Sandstø 2012
*/
#ifndef WORLD_H
#define WORLD_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800

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

    float GetFrameTime()
    {
        return m_window.GetFrameTime();
    }
private:
    World() {}
    World(const World&) {}
    World operator =(const World&) {}

    sf::RenderWindow m_window;///< Handle the window.
};

#define gWorld World::Instance()
#define gWindow gWorld.GetWindow()
#endif