#include "Wall.h"
#include "ResourceMgr.h"
#include "World.h"

Wall::Wall(const Vec2D &startPoint, const Vec2D &endPoint)
{
    m_type = ENTITY_WALL;
    m_rect = sf::Shape::Line(*(sf::Vector2f*)&startPoint, *(sf::Vector2f*)&endPoint, 30.0, sf::Color(0, 0, 0));

    m_startPoint = startPoint;
    m_endPoint = endPoint;
}

void Wall::SetPosition(const Vec2D &pos)
{
    m_position = pos;
}

void Wall::Setup(const Vec2D &startPoint, const Vec2D &endPoint)
{
    Vec2D newStartPos = startPoint + gWorld.GetCameraPos();
    Vec2D newEndPos = endPoint + gWorld.GetCameraPos();
    m_rect = sf::Shape::Line(*(sf::Vector2f*)&newStartPos, *(sf::Vector2f*)&newEndPos, 30.0, sf::Color(0, 0, 0));
    m_startPoint = startPoint;
    m_endPoint = endPoint;
}

void Wall::Draw(Real duration)
{
    Vec2D newStartPos = m_startPoint + gWorld.GetCameraPos();
    Vec2D newEndPos = m_endPoint + gWorld.GetCameraPos();
    m_rect = sf::Shape::Line(*(sf::Vector2f*)&newStartPos, *(sf::Vector2f*)&newEndPos, 30.0, sf::Color(0, 0, 0));
    gWorld.GetWindow()->Draw(m_rect);
}

void Wall::GetCornerPoints(CornerPoints &points)
{
}