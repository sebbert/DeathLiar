#include "Pistol.h"
#include "Weapon.h"

Pistol::Pistol()
{
    m_secBetweenShots = 0.25f;
    m_clock.Reset();
}

void Pistol::Fire()
{
    if(m_clock.GetElapsedTime() > (Real)m_secBetweenShots)
    {
        Vec2D force = m_heading.Opposite() * 500.0;
        gBulletMgr.FireBullet("Media/pistolBullet.png", 0.5, 35, 1, 1, m_position, force);
        m_clock.Reset();
    }
}