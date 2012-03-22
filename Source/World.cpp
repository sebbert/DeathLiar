#include "World.h"

void World::Init()
{
    m_window.Create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Deathliar", sf::Style::Fullscreen);
    m_window.SetFramerateLimit(30);
}

void World::Destroy()
{
}