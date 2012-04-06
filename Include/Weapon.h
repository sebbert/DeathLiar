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

#ifndef WEAPON_H_
#define WEAPON_H_

#include "Entity.h"
#include <vector>

class Weapon : public Entity
{
public:
    /**
     * The constructor.
     * Inits the weapon with custom settings, or uses axe settings (takes no damage) if no arguments are specified.
     * @param damage How much damage the weapon makes for each hit.
     * @param maxHealth The maximum health of the weapon. The health will also be set to this.
     * @param weaponDamage How much damage the weapon takes each hit.
     */
    Weapon(int damage = 1, int maxHealth = 1, int weaponDamage = 0);
    

    /**
     * Fires or starts firing the weapon.
     * Should be called on mouse down.
     */
    virtual void Fire() {}

    /**
     * Stops hitting.
     * Should be called on mouse release.
     */
    virtual void StopFire() {}

    /**
     * Sets how much damage the weapon makes for each hit.
     * @param damage How much damage the weapon should make.
     */
    void SetDamage(int damage)
    {
        m_Damage = damage;
    }

    /**
     * Sets the weapons health (e.g. the amount of bullets in a gun).
     * @param weaponHealth The weapon's health.
     */
    void SetWeaponHealth(int weaponHealth)
    {
        m_WeaponHealth = weaponHealth;
    }

    /**
     * Sets the weapon's maximum health.
     * @param maxHealth The weapon's maximum health.
     */
    void SetMaxHealth(int maxHealth)
    {
        m_MaxHealth = maxHealth;
    }

    /**
     * Sets how much damage the weapon makes each hit.
     * @param weaponDamage How much damage the weapon should take each hit.
     */
    void SetWeaponDamage(int weaponDamage)
    {
        m_WeaponDamage = weaponDamage;
    }

    int m_Damage;       ///< How much damage the weapon makes for each hit.
    int m_WeaponHealth; ///< The weapon's health, e.g. how many bullets are in a gun. Ranges from 0 to m_MaxHealth.
    int m_MaxHealth;    ///< The maximum health of the weapon.
    int m_WeaponDamage; ///< How much damage the weapon takes each hit.
    bool m_isHitting;   ///< Wether the weapon is currently hitting or not.

protected:
    Vec2D m_hitOffset;
};

/**
 * Bullet is a special form of weapon. It is fired by a weapon.
 */
class Bullet : public Weapon
{
public:
    Bullet();
    Bullet(Real mass, int damage, int maxHealth, int weaponDamage, Vec2D &startPos, Vec2D &force);
    void Update(Real duration);

    Real m_mass;
    Real m_oneOverMass;
    Vec2D m_velocity;
};

/**
 * BulletManager handles the bullets fired in the world.
 */
class BulletManager
{
public:
    void Init();

    /**
     * Fire a bullet.
     */
    void FireBullet(const char *image, Real mass, int damage, int maxHealth, int weaponDamage, Vec2D &startPos, Vec2D &force);

    /**
     * Update all the bullets and destroy them if necessary.
     */
    void Update(Real duration);

    /**
     * Resolves collisions betweens bullets and a entity.
     */ 
    void ResolveCollisions(CreatureEntity *entity);

    static BulletManager &Instance()
    {
        static BulletManager instance;
        return instance;
    }

    typedef std::vector<Bullet>::iterator BulletIter;
    std::vector<Bullet> m_bullets;
private:
    /**
     * Prevent constructor, copy constructor, and copy operator to be called outside of class.
     */
    BulletManager() {}
    BulletManager(const BulletManager&) {}
    void operator =(const BulletManager&){}
};

#define gBulletMgr BulletManager::Instance()

#endif
