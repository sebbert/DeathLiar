#include "Pistol.h"
#include "Weapon.h"

void Pistol::Fire()
{
    Vec2D force = m_heading.Opposite() * 500.0;
    gBulletMgr.FireBullet("Media/pistolBullet.png", 0.5, 100, 20, 10, m_position, force);
}