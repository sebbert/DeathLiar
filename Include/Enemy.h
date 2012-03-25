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

#ifndef ENEMY_H
#define ENEMY_H

#include "MathUtil.h"
#include "Vec2D.h"
#include "Entity.h"
#include "World.h"

/**
 * An enemy class. This should be used for zombies, etc.
 */
class Enemy : public Entity
{
public:
	/**
	 * The constructor. Calls the Init method.
	 */
	Enemy();

	/**
	 * The destructor. Calls the Destroy method.
	 */
	~Enemy();

	/**
	 * Initalizes the enemy.
	 */
	virtual void Init() = 0;

	/**
	 * Destroys the enemy.
	 */
	virtual void Destroy() = 0;

	/**
	 * Sets the players position.
	 * @param pos The players position.
	 */
	void SetPlayerPosition(Vec2D& pos);

    void SetPosition(Vec2D& pos);

	/**
	 * Updates the AI.
	 */
	void Update(Real duration);

	/**
	 * Sets the speed of the enemy.
	 * @param speed The speed.
	 */
	void SetSpeed(Real speed);

	/**
	 * Sets the amount of lives.
	 * @param lives The amount of lives.
	 */
	void SetLives(int lives);

	/**
	 * Sets the maximum amount of lives.
	 * @param maxLives The amount of lives.
	 */
	void SetMaxLives(int maxLives);

	/**
	 * Sets the health.
	 */
	void SetHealth(int health);

	/**
	 * Sets the maximum health.
	 * @param maxHealth The maximum health.
	 */
	void SetMaxHealth(int maxHealth);

	/**
	 * Damages the enemy. Removes 1 health.
	 */
	virtual void Damage();

	/**
	 * Hurts the enemy. Removes 1 life and sets the health to full.
	 */
	virtual void Hurt();

	/**
	 * Kills the enemy. Removes all lives.
	 */
	virtual void Kill();

private:
	Vec2D m_PlayerPosition;	///< The players position.
	Real m_Speed;			///< The speed of the enemy.

	int m_MaxLives;			///< The maximum amount of lives.
	int m_Lives;			///< The amount of lives.

	int m_MaxHealth;		///< The maximum health.
	int m_Health;			///< The amount of health.
};

#endif /* ENEMY_H */
