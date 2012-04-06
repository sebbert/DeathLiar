#include "Pistol.h"
#include "Weapon.h"
#include "World.h"

Pistol::Pistol()
{
    m_secBetweenShots = 0.25f;
    m_clock.Reset();
    SetSprite("Media/weapon_pistol.png");
}

void Pistol::Fire()
{
    if(m_clock.GetElapsedTime() > (Real)m_secBetweenShots)
    {
        Real rad = DegToRad(angle);
        Vec2D force = m_heading.Opposite() * 500.0;
        Vec2D pos = m_position + Vec2D(35, 20).Rotate(-rad);
//        Vec2D toCenter = pos - gWorld.GetPlayer().GetPosition();
//        toCenter.Rotate(rad);
//        pos += toCenter;

        gBulletMgr.FireBullet("Media/pistolBullet.png", 0.5, 35, 1, 1, pos, force);
        m_clock.Reset();
    }
}