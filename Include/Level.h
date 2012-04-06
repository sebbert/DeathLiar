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
* Copyright � 2012 Emil Sandst�, Sebastian Reinhard
* 
*/
#ifndef LEVEL_H_
#define LEVEL_H_

#include <SFML/Graphics.hpp>
#include "Vec2D.h"
#include "Entity.h"

class Level
{
public:
    void Init(const char *levelName);

    void Destroy();

    void Draw();

    int GetZoneFromPoint(const Vec2D &point);

    const std::string &GetPathToLevel()
    {
        return m_path;
    }

    Entity **GetEntities()
    {
        return m_entities;
    }

    bool CollisionWithWalls(Entity *entity);

    int m_levelWidth;
    int m_levelHeight;
private:
    sf::Sprite m_zones[9];///< Zones of the scrolling background. Each zone is 1024x1024 pixels wide.
    Vec2D m_zonePositions[9];///< Positions of the zones.
    Entity **m_entities;///< Dynamic array.
    int m_numEntities;///< Number of entities in the array of pointers to entities.
    std::string m_path;///< Path to level folder.
};

#endif