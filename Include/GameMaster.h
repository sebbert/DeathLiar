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
#ifndef GAME_MASTER_H_
#define GAME_MASTER_H_

#include "Enemy.h"
#include <vector>

/**
 * Game master controls the waves of enemies, and where/when weapons are spawned, etc.
 */
class GameMaster
{
public:
    /**
     * Initialize game master.
     */
    void Init();

    /**
     * Free memory, and unload everything.
     */
    void Destroy();

    /**
     * Updates game master, which includes but no excludes:
     * - Enemies are drawn.
     * - Updates triggers, which includes updating of weapons.
     */
    void Update(Real duration);

    void ResolveCollision(CreatureEntity *entity);

    static GameMaster &Instance()
    {
        static GameMaster instance;
        return instance;
    }

    unsigned char GetWave()
    {
        return m_wave;
    }
private:
    GameMaster() {}
    GameMaster(const GameMaster &) {}
    GameMaster operator=(const GameMaster &) {}

    void Separation();

    /**
     * Called when all the enemies have died.
     */
    void NewWave();

    Enemy *m_enemies;
    short m_numEnemies;
    unsigned char m_wave;///< Current wave.
};

#define gGameMaster GameMaster::Instance()

#endif