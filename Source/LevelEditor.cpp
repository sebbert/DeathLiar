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

    m_startPoint.Set(-1, -1);

    // Maxium entities in the level.
    m_entities = new Entity*[m_maxNumberEntities];
    m_wallIcon.SetImage(*gResourceMgr.GetImage("Media/LevelEditor/wallIcon.png"));
    m_wallIcon.SetPosition((Real)gWorld.GetParams().m_windowWidth - 32, 32); 
    m_wallIcon.SetCenter(64 * (Real)0.5, 64 * (Real)0.5);

    for(int i = 0;i < m_maxNumberEntities;i++)
    {
        m_entities[i] = 0;
    }
}

void LevelEditor::Destroy()
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

void LevelEditor::Save(const char *fileName)
{
}

bool LevelEditor::Load(const char *fileName)
{
    return true;
}

void LevelEditor::HandleEvents(sf::Event &event)
{
    if(event.Type == sf::Event::MouseButtonPressed)
    {
        if(event.MouseButton.Button == sf::Mouse::Left)
        {
            Vec2D mousePos((Real)event.MouseButton.X, (Real)event.MouseButton.Y);

            //Drawing of walls are handled different from other entities.
            if(m_currentTool == WALL)
            {
                if(m_startPoint.x < 0 || m_startPoint.y < 0)
                {
                    m_startPoint = mousePos;
                    AddEntity(mousePos);
                }
                else
                {
                    m_pEntity = 0;
                    m_startPoint.Set(-1, -1);
                    m_currentTool = 1;
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
                else if(!SetEntity(mousePos))
                {
                    AddEntity(mousePos);
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

                wall->GetShape() = sf::Shape::Line(*(sf::Vector2f*)&m_startPoint, *(sf::Vector2f*)&mousePos, 30.0, sf::Color(0, 0, 0));
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

        if(event.Key.Code == sf::Key::Down)
        {
            if(m_pCurrentEntity != 0)
            {
                m_pCurrentEntity->GetSprite().Rotate(45.0f);
            }
        }

        if(event.Key.Code == sf::Key::Right)
        {
            if(m_pCurrentEntity != 0)
            {
                m_pCurrentEntity->GetSprite().Rotate(-1.0f);
            }
        }

        if(event.Key.Code == sf::Key::Left)
        {
            if(m_pCurrentEntity != 0)
            {
                m_pCurrentEntity->GetSprite().Rotate(1.0f);
            }
        }
    }
}

void LevelEditor::Draw()
{
    gWorld.GetWindow()->Draw(m_wallIcon);

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
    default:
        std::cout << "You have not yet picked a tool.\n";
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
        if(PointIsInside(mousePos, m_entities[i]->GetSprite()))
            return m_entities[i];
    }

    return 0;
}
