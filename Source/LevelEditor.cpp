#include "LevelEditor.h"
#include "ResourceMgr.h"
#include "Enemy.h"
#include "Wall.h"
#include "World.h"

void LevelEditor::Init()
{
    m_wallIcon.SetImage(*gResourceMgr.GetImage("Media/LevelEditor/wallIcon.png"));
    m_wallIcon.SetCenter(32, 32);
    m_wallIcon.SetPosition(gWorld.GetParams().m_windowWidth - 32, 2 * 64);

    m_spawnIcon.SetImage(*gResourceMgr.GetImage("Media/LevelEditor/spawnIcon.png"));
    m_spawnIcon.SetCenter(32, 32);
    m_spawnIcon.SetPosition(gWorld.GetParams().m_windowWidth - 32, 3 * 64);
}

void LevelEditor::HandleEvents(sf::Event &event)
{
    if(event.Type == sf::Event::MouseButtonPressed)
    {
        if(event.MouseButton.Button == sf::Mouse::Left)
        {
            Vec2D mousePos((Real)event.MouseButton.X, (Real)event.MouseButton.Y);

            if(!SetTool(mousePos))
            {
                Entity *entity = 0;
                switch(m_currentTool)
                {
                case WALL:
                    entity = new Wall();
                    break;
                case ENEMY_SPAWN_POINT:
                    entity = new EnemySpawnPoint();
                    break;
                };

                if(entity)
                {
                    mousePos += gWorld.m_camera.m_position.Opposite();
                    int cell = gWorld.GetLevel().GetCellFromPoint(mousePos);
                    entity->SetPosition(gWorld.GetLevel().SnapToCenter(mousePos));
                    gWorld.GetLevel().AddEntity(cell, entity);
                }
            }
        }
    }
}

/**
* Set entity to be added to level, if mouse pressed occured inside the level editor side bar.
*/
bool LevelEditor::SetTool(Vec2D &mousePos)
{
    if(PointIsInside(mousePos, m_wallIcon))
    {
        m_currentTool = WALL;
        return true;
    }

    if(PointIsInside(mousePos, m_spawnIcon))
    {
        m_currentTool = ENEMY_SPAWN_POINT;
        return true;
    }

    return false;
}

void LevelEditor::Draw()
{
    gWorld.GetWindow()->Draw(m_wallIcon);
    gWorld.GetWindow()->Draw(m_spawnIcon);
}