#include "Wall.h"
#include "ResourceMgr.h"
#include "World.h"

Wall::Wall(const Vec2D &startPoint, const Vec2D &endPoint)
{
    m_rect = sf::Shape::Line(*(sf::Vector2f*)&startPoint, *(sf::Vector2f*)&endPoint, 30.0, sf::Color(0, 0, 0));

    SetSprite("Media/Levels/Wall.png");
    m_sprite.SetRotation(atan2(m_normal.y, m_normal.x));
}

void Wall::Draw(Real duration)
{
    gWorld.GetWindow()->Draw(m_rect);
}