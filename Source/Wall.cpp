#include "Wall.h"
#include "ResourceMgr.h"

Wall::Wall(const Vec2D &normal)
{
    m_normal = normal;

    m_sprite.SetImage(*gResourceMgr.GetImage("Media/Levels/Wall.png"));
    m_sprite.SetRotation(atan2(m_normal.y, m_normal.x));
}

