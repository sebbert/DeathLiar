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

    void Destroy();

    /** 
     * Save a level.
     * @param fileName Name of level to save.
     */
    void Save(const char *fileName);

    /** 
     * Load a level.
     * @param fileName Name of level to load.
     */
    bool Load(const char *fileName);

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
    bool SetEntity(Vec2D &mousePos);

    Entity *OverEntities(Vec2D &mousePos);

    /**
     * Create a entity on the map. Entities can be weapons, walls or other in game elements.
     */
    void AddEntity(Vec2D &mousePos);

    enum Tools{WALL};

    int m_maxNumberEntities;
    int m_currentEntity;///< Current entity to be added to level if mouse left is pressed.
    unsigned m_currentTool;

    sf::Sprite m_wallIcon;///< Icon for wall.
    sf::Sprite m_weaponIcon;///< Icon for weapon.

    Entity *m_pCurrentEntity;
    Entity *m_pEntity;///< Pointer to entity.
    Entity **m_entities;///< A fixed size dynamic array of entities.
};

#endif