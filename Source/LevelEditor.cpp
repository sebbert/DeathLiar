#include "LevelEditor.h"
#include "ResourceMgr.h"
#include "Enemy.h"
#include "Wall.h"
#include "World.h"

void LevelEditor::Init()
{
    m_maxNumberEntities = 200;
    m_pEntity = 0;
    m_pCurrentEntity = 0;
    m_currentTool = -1;

    m_startPoint.Set(-1, -1);

    // Maxium entities in the level.
    m_entities = new Entity*[m_maxNumberEntities];
    
    m_wallIcon.SetImage(*gResourceMgr.GetImage("Media/LevelEditor/wallIcon.png"));
    m_wallIcon.SetCenter(32, 32);
    m_wallIcon.SetPosition(gWorld.GetParams().m_windowWidth - (Real)32, (Real)32); 

    m_enemyIcon.SetImage(*gResourceMgr.GetImage("Media/LevelEditor/zombieIcon.png"));
    m_enemyIcon.SetCenter(32, 32);
    m_enemyIcon.SetPosition(gWorld.GetParams().m_windowWidth - (Real)32, (Real)96); 

    /*std::string path = gWorld.GetLevel().GetPathToLevel();
    path += "/level.dat";
    Load(path.c_str());*/

    for(int i = 0;i < m_maxNumberEntities;i++)
    {
        m_entities[i] = 0;
    }
}

void LevelEditor::Destroy()
{
    if(m_entities != 0)
    {
        for(int i = 0;i < m_maxNumberEntities;i++)
        {
            if(m_entities[i] == 0)
            {
                delete m_entities[i];
            }
        }
        delete []m_entities;
        m_entities = 0;
    }
}

void LevelEditor::Save(const char *fileName)
{
    std::ofstream file(fileName, std::ios::binary);
    file.write((char*)&m_currentEntity, sizeof(char));
    for(int i = 0;i < m_currentEntity;i++)
    {
        int type = m_entities[i]->GetType();
        file.write((char*)&type, sizeof(char));
        if(type == ENTITY_WALL)
        {
            Wall *pWall = static_cast<Wall*>(m_entities[i]);
            file.write((char*)&pWall->m_startPoint, sizeof(Vec2D));
            file.write((char*)&pWall->m_endPoint, sizeof(Vec2D));
        }
        else
        {
            file.write((char*)&m_entities[i]->GetPosition(), sizeof(Vec2D));
            Real rot = m_entities[i]->GetRotation();
            file.write((char*)&rot, sizeof(Real));
        }
    }

    file.close();
}

bool LevelEditor::Load(const char *fileName)
{
    std::ifstream file(fileName, std::ios::binary);

    if(!file.is_open())
    {
        std::cout << "Failed to load file: " << fileName << std::endl;
        return false;
    }

    file.read((char*)&m_currentEntity, sizeof(char));
    for(int i = 0;i < m_currentEntity;i++)
    {
        char type;
        file.read(&type, sizeof(char));

        if(type == ENTITY_WALL)
        {
            Vec2D startPoint;
            Vec2D endPoint;
            file.read((char*)&startPoint, sizeof(Vec2D));
            file.read((char*)&endPoint, sizeof(Vec2D));
            m_entities[i] = new Wall(startPoint, endPoint);
        }
        else
        {
            Vec2D position;
            Real rot;

            file.read((char*)&position, sizeof(Vec2D));
            file.read((char*)&rot, sizeof(Real));

            m_entities[i]->GetSprite().SetRotation(rot);
        }
    }

    file.close();

    return true;
}

void LevelEditor::HandleEvents(sf::Event &event)
{
    if(event.Type == sf::Event::MouseButtonPressed)
    {
        if(event.MouseButton.Button == sf::Mouse::Left)
        {
            Vec2D mousePos((Real)event.MouseButton.X, (Real)event.MouseButton.Y);

            bool setTool = SetEntity(mousePos);

            //Drawing of walls are handled different from other entities.
            if(m_currentTool == WALL && !setTool)
            {/*
                for(int i = 0;i < m_currentEntity;i++)
                {
                    if(m_entities[i]->GetType() == ENTITY_WALL)
                    {   
                        CornerPoints points;
                        Wall *pWall = static_cast<Wall*>(m_entities[i]);
                        pWall->GetCornerPoints(points);
                        if(PointIsInsideOOB(mousePos, points.topLeft, points.bottomLeft, points.topRight, points.bottomRight))
                        {
                            m_pCurrentEntity = pWall;
                        }
                    }
                }
                */
                if(m_startPoint.x < 0 || m_startPoint.y < 0)
                {
                    m_startPoint = mousePos;
                    AddEntity(mousePos);
                }
                else
                {
                    m_pEntity = 0;
                    m_startPoint.Set(-1, -1);
                }
            }
            else
            {
                Entity *pressedEntity = 0;
                if(m_pCurrentEntity != 0)
                {
                    m_pCurrentEntity = 0;
                }
                else if((pressedEntity = OverEntities(mousePos)) != 0)
                {
                    m_pCurrentEntity = pressedEntity;
                }
                else if(!setTool)
                {
                    AddEntity(mousePos);
                }
            }
        }
        else if(event.MouseButton.Button == sf::Mouse::Right)
        {
            if(m_currentTool == WALL)
            {
                m_currentTool = SELECT;
                if(m_pEntity != 0 && m_pEntity->GetType() == ENTITY_WALL)
                {
                    delete m_pEntity;
                    --m_currentEntity;
                    m_pEntity = 0;
                    m_startPoint.Set(-1, -1);
                }
            }
        }
    }

    if(event.Type == sf::Event::MouseMoved)
    {
        if(m_pCurrentEntity != 0)
        {
            Vec2D mousePos((Real)event.MouseMove.X, (Real)event.MouseMove.Y);
            m_pCurrentEntity->SetPosition(mousePos);
        }

        if(m_currentTool == WALL)
        {
            if(m_startPoint.x > 0 && m_startPoint.y > 0)
            {
                Vec2D mousePos((Real)event.MouseMove.X, (Real)event.MouseMove.Y);
                Wall *wall;
                wall = static_cast<Wall*>(m_pEntity);

                wall->Setup(m_startPoint, mousePos);
            }
        }
    }

    if(event.Type == sf::Event::KeyPressed)
    {
        if(event.Key.Code == sf::Key::Up)
        {
            if(m_pCurrentEntity != 0)
            {
                m_pCurrentEntity->GetSprite().Rotate(-45.0f);
            }
        }
        else if(event.Key.Code == sf::Key::Down)
        {
            if(m_pCurrentEntity != 0)
            {
                m_pCurrentEntity->GetSprite().Rotate(45.0f);
            }
        }
        else if(event.Key.Code == sf::Key::Right)
        {
            if(m_pCurrentEntity != 0)
            {
                m_pCurrentEntity->GetSprite().Rotate(-1.0f);
            }
        }
        else if(event.Key.Code == sf::Key::Left)
        {
            if(m_pCurrentEntity != 0)
            {
                m_pCurrentEntity->GetSprite().Rotate(1.0f);
            }
        }
        else if(event.Key.Code == sf::Key::S && event.Key.Control)
        {
            std::string path = gWorld.GetLevel().GetPathToLevel();
            path += "/level.dat";
            Save(path.c_str());
        }
        else if(event.Key.Code == sf::Key::O && event.Key.Control)
        {
            std::string path = gWorld.GetLevel().GetPathToLevel();
            path += "/level.dat";
            Load(path.c_str());
        }
    }
}

void LevelEditor::Draw()
{
    gWorld.GetWindow()->Draw(m_wallIcon);
    gWorld.GetWindow()->Draw(m_enemyIcon);

    for(int i = 0;i < m_currentEntity;i++)
    {
        if(m_entities[i] != 0)
            m_entities[i]->Draw((Real)0.0);
    }
}

bool LevelEditor::SetEntity(Vec2D &mousePos)
{
    if(PointIsInside(mousePos, m_wallIcon))
    {
        m_currentTool = WALL;
        return true;
    }

    if(PointIsInside(mousePos, m_enemyIcon))
    {
        m_currentTool = ENEMY_SPAWN_POINT;
        return true;
    }

    return false;
}

void LevelEditor::AddEntity(Vec2D &mousePos)
{
    //Switch between tools based on current tool.
    switch(m_currentTool)
    {
    case WALL:
        m_pEntity = new Wall(m_startPoint, m_startPoint); 
        break;
    case ENEMY_SPAWN_POINT:
        m_pEntity = new EnemySpawnPoint();
        break;
    default:
        std::cout << "You have not yet picked a tool.\n";
        break;
    }

    if(m_pEntity != 0)
    {
        if(m_maxNumberEntities > m_currentEntity)
        {
            m_entities[m_currentEntity++] = m_pEntity;
        }
        else
        {
            std::cout << "Each level have only support for 200 entities. Sorry\n";
        }
        m_pEntity->SetPosition(mousePos);
    }
}

Entity *LevelEditor::OverEntities(Vec2D &mousePos)
{
    for(int i = 0;i < m_currentEntity;i++)
    {
        if(m_entities[i]->GetType() != ENTITY_WALL && m_entities[i]->GetType() != ENTITY_SPAWN_POINT)
        {
            if(PointIsInside(mousePos, m_entities[i]->GetSprite()))
                return m_entities[i];
        }
    }

    return 0;
}
