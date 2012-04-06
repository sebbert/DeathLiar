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
#ifndef WALL_H_
#define WALL_H_

#include "Entity.h"

struct CornerPoints
{
    Vec2D topRight;
    Vec2D topLeft;
    Vec2D bottomLeft;
    Vec2D bottomRight;
};

/**
 * Wall is a solid entity which are used to make safe spot for the player.
 * A wall has a normal which makes the wall solid on one side and not on the other side.
 */
class Wall : public Entity
{
public:
    /**
     * Constructor
     */
    Wall(const Vec2D &startPoint, const Vec2D &endPoint);

    void Setup(const Vec2D &startPoint, const Vec2D &endPoint);

    void SetPosition(const Vec2D &pos);

    /**
     * Draw the wall.
     */
    void Draw(Real duration);

    sf::Shape &GetShape()
    {
        return m_rect;
    }

    void GetCornerPoints(CornerPoints &points);

    Vec2D m_startPoint;
    Vec2D m_endPoint;
private:
    Vec2D m_normal;///< A normal which specifies where on the wall it is solid.
    sf::Shape m_rect;
};

#endif