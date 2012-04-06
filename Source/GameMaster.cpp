#include "GameMaster.h"
#include "World.h"

GameMaster::~GameMaster()
{
    Destroy();
}

void GameMaster::Init()
{
    //Maxium number of enemies on the map at any time.
    m_enemies = new Enemy[200];
    NewWave();
}

void GameMaster::Destroy()
{
    if(m_enemies)
    {
        delete []m_enemies;
        m_enemies = 0;
    }

    m_wave = 0;
}

void GameMaster::NewWave()
{
    ++m_wave;
    m_numEnemies = m_wave * 5;
    for(int i = 0;i < m_numEnemies;i++)
    {
        Vec2D pos((Real)sf::Randomizer::Random(0, gWorld.GetLevel().m_levelWidth), (Real)sf::Randomizer::Random(0, gWorld.GetLevel().m_levelHeight));
        m_enemies[i].Init(100, gWorld.GetParams().m_enemySpeed, 1.0, "Media/Zombie.png");
        m_enemies[i].SetPosition(pos);
    }
}

void GameMaster::Update(Real duration)
{
    bool isEnemiesDead = true;
    for(int i = 0;i < m_numEnemies;i++)
    {
        if(m_enemies[i].m_health > 0)
        {
            isEnemiesDead = false;
            Separation();
            m_enemies[i].Draw(duration);
        }
    }

    if(isEnemiesDead)
    {
        std::cout << "All enemies are dead...new wave!" << std::endl;
        NewWave();
        std::cout << "You are on wave: " << (int)m_wave << "\nGood Work! So long, haha!\n";
    }
}

void GameMaster::ResolveCollision(CreatureEntity *entity)
{
    for(int i = 0;i < m_numEnemies;i++)
    {
        if(gWorld.GetLevel().GetZoneFromPoint(m_enemies[i].GetPosition()) == 
            gWorld.GetLevel().GetZoneFromPoint(entity->GetPosition()))
        {
            Vec2D between = entity->GetPosition() - 
                (m_enemies[i].GetPosition() + (m_enemies[i].m_velocity * gWorld.GetFrameTime()));
            if(between.MagnitudeSquared() < m_enemies[i].m_halfWidth * m_enemies[i].m_halfWidth + entity->m_halfWidth * entity->m_halfWidth)
            {
                entity->m_health -= 10;
                m_enemies[i].GetPosition() -= m_enemies[i].m_velocity * gWorld.GetFrameTime();
            }
        }
    }
}

void GameMaster::Separation()
{
    for(int i = 0;i < m_numEnemies;i++)
    {
        int zone = gWorld.GetLevel().GetZoneFromPoint(m_enemies[i].GetPosition());
        for(int j = 0;j < m_numEnemies;j++)
        {
            if(i != j)
            {
                if(zone == gWorld.GetLevel().GetZoneFromPoint(m_enemies[j].GetPosition()))
                {
                    Vec2D between = m_enemies[j].GetPosition() - m_enemies[i].GetPosition();
                    if(between.MagnitudeSquared() < 2 * m_enemies[i].m_halfWidth * m_enemies[i].m_halfWidth)
                    {
                        //between.Normalize();
                        //Vec2D force = between * m_enemies[j].GetSpeed() * gWorld.GetFrameTime();
                        m_enemies[j].m_velocity += between * gWorld.GetFrameTime();
                    }
                }
            }
        }
    }
}