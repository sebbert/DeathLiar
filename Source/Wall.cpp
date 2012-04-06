#include "Wall.h"
#include "ResourceMgr.h"
#include "World.h"

Wall::Wall(const Vec2D &startPoint, const Vec2D &endPoint)
{
    m_type = ENTITY_WALL;
    m_rect = sf::Shape::Rectangle(*(sf::Vector2f*)&startPoint, *(sf::Vector2f*)&endPoint, sf::Color(0, 0, 0));

    m_startPoint = startPoint;
    m_endPoint = endPoint;
}

void Wall::SetPosition(const Vec2D &pos)
{
    m_position = pos;
}

void Wall::Setup(const Vec2D &startPoint, const Vec2D &endPoint)
{
    m_startPoint = startPoint + gWorld.GetCameraPos().Opposite();
    m_endPoint = endPoint + gWorld.GetCameraPos().Opposite();

    m_rect = sf::Shape::Rectangle(*(sf::Vector2f*)&m_startPoint, *(sf::Vector2f*)&m_endPoint, sf::Color(0, 0, 0));
}

void Wall::Draw(Real duration)
{
    m_rect.SetPosition(*(sf::Vector2f*)&gWorld.GetCameraPos());
    gWorld.GetWindow()->Draw(m_rect);
}