#ifndef ENTITY_H_
#define ENTITY_H_

#include "Vec2D.h"

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
    
    static sf::Uint16 GetNextID()
    {
        return Entity::sNextID++;
    }

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
    
    /**
     * Virtual function which does nothing.
     */
    virtual void Update(Real duration);
    
    /**
     * Virtual function which renders a sprite.
     */
    virtual void Draw(Real duration);

protected:
    Vec2D m_position;///< Position of a entity.
    sf::Sprite m_sprite;///< Sprite of a entity.
    sf::Uint16 m_id;///< ID of sprite.
    static sf::Uint16 sNextID;///< ID for the next entity created.
};

#endif