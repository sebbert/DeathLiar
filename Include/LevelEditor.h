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
#ifndef LEVEL_EDITOR_H_
#define LEVEL_EDITOR_H_

#include "SFML/Graphics.hpp"
#include "Entity.h"

/**
 * Level editor is used to create levels.
 */
class LevelEditor
{
public:
    void Init();

    /** 
     * Handle events, mainly mouse.
     * @param event Event handler.
     */ 
    void HandleEvents(sf::Event &event);

    /**
     * Draw level editor option bar.
     */
    void Draw();
private:
    /**
     * Set entity to be added to level, if mouse pressed occured inside the level editor side bar.
     */
    bool SetTool(Vec2D &mousePos);

    Entity *OverEntities(Vec2D &mousePos);

    /**
     * Creates a entity on the map. Entities can be weapons, walls or other in game elements.
     */
    void AddEntity(Vec2D &mousePos);

    enum Tools{SELECT, WALL, ENEMY_SPAWN_POINT};///< Types of tools
    unsigned m_currentTool;///< The current tool.

    sf::Sprite m_selectIcon;
    sf::Sprite m_wallIcon;
    sf::Sprite m_spawnIcon;
};

#endif