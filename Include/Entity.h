#ifndef ENTITY_H
#define ENTITY_H

#include "World.h"
#include "Vec2D.h"

/**
 * Entity is an object which can be rendered very easily.
 */
class Entity
{
public:
    void SetSprite(sf::Image &image);
    bool SetSprite(const char *fileName);
    
    virtual void Update(Real duration);
    virtual void Draw(Real duration);
protected:
    Vec2D m_position;///< Position of a entity.
    sf::Sprite m_sprite;///< Sprite of a entity.
};

#endif