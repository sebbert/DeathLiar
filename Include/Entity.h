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

#ifndef ENTITY_H_
#define ENTITY_H_

#include "Vec2D.h"
#include <SFML/Graphics.hpp>

/**
 * Entity is an object in the game world which can easily be rendered.
 */
class Entity
{
public:
    /**
     * Overload default constructor.
     */
    Entity();

    /**
     * Set sprite of entity, by an image.
     * @param image Image to bind with sprite.
     */
    void SetSprite(sf::Image &image);
    
    /**
     * Set sprite of entity, by a image file.
     * If image have been loaded before, it will be used.
     */
    bool SetSprite(const char *fileName);
    
    void SetPosition(const Vec2D &pos);

    /**
     * Virtual function which does nothing.
     */
    virtual void Update(Real duration);
    
    /**
     * Virtual function which renders a sprite.
     */
    virtual void Draw(Real duration);

    /**
     * Returns the position of the entity.
     * @return the position of the entity.
     */
    Vec2D& GetPosition()
    {
        return m_position;
    }

protected:
    static sf::Uint16 GetNextID()
    {
        return Entity::sNextID++;
    }

    Vec2D m_position;           ///< Position of a entity.
    sf::Sprite m_sprite;        ///< Sprite of a entity.
    sf::Uint16 m_id;            ///< ID of sprite.
    static sf::Uint16 sNextID;  ///< ID for the next entity created.
};

#endif