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
#include <map>
#include "Vec2D.h"
#include "Entity.h"


class Level
{
public:
    ~Level();

    void Init(const char *levelName);

    bool LoadLevelInfo();

    void SaveLevelInfo();

    void Destroy();

    void Draw();

    int GetZoneFromPoint(const Vec2D &point);

    int GetCellFromPoint(const Vec2D &point);

    void RemoveEntityFromCell(int cell);

    Entity *GetEntityFromCell(int cell);

    Vec2D GetCenterOfCell(int cell);

    Vec2D SnapToCenter(const Vec2D &point);

    /**
     * Add entity to cell.
     */
    void AddEntity(int cell, Entity *entity);

    const std::string &GetPathToLevel()
    {
        return m_path;
    }

    bool CollisionWithWalls(Entity *entity);

    int m_levelWidth;
    int m_levelHeight;
private:
    sf::Sprite m_zones[9];///< Zones of the scrolling background. Each zone is 1024x1024 pixels wide.
    Vec2D m_zonePositions[9];///< Positions of the zones.
    Vec2D m_gridSize;///< Grid size.
    int m_gridExtentX;///< How many grid cells in the x direction
    int m_gridExtentY;///< How many grid cells in the y direction.

    typedef std::map<int, Entity*>::iterator EntityIter;
    std::map<int, Entity*> m_entities; ///< Entities, sorted by which cell they belong to.

    std::string m_path;///< Path to level folder.
};

#endif