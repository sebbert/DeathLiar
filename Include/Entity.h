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
    
    void Draw();
protected:
    Vec2D m_position;
    sf::Sprite m_sprite;
};

#endif