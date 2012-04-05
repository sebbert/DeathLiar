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

    // Maxium entities in the level.
    m_entities = new Entity*[m_maxNumberEntities];
    m_wallIcon.SetImage(*gResourceMgr.GetImage("Media/LevelEditor/wallIcon.png"));
    m_wallIcon.SetPosition((Real)gWorld.GetParams().m_windowWidth - 64, 10); 

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

            Entity *pressedEntity = OverEntities(mousePos);
            if(pressedEntity != 0)
            {
                m_pCurrentEntity = pressedEntity;
            }
            else if(!SetEntity(mousePos))
            {
                AddEntity(mousePos);
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
    sf::Rect<Real> rect(m_wallIcon.GetPosition().x, m_wallIcon.GetPosition().y, 
        m_wallIcon.GetPosition().x + m_wallIcon.GetImage()->GetWidth(), m_wallIcon.GetPosition().y + m_wallIcon.GetImage()->GetHeight());
    if(PointIsInside(mousePos, rect))
    {
        m_currentTool = WALL;
        return true;
    }

    return false;
}

void LevelEditor::AddEntity(Vec2D &mousePos)
{
    Vec2D right(1, 0);
    //Switch between tools based on current tool.
    switch(m_currentTool)
    {
    case WALL:
        m_pEntity = new Wall(right);
        break;
    default:
        std::cout << "You have not yet picked a tool.\n";
    }

    if(m_pEntity != 0)
    {
        m_entities[m_currentEntity++] = m_pEntity;
        m_pEntity->SetPosition(mousePos);
    }
}

Entity *LevelEditor::OverEntities(Vec2D &mousePos)
{
    for(int i = 0;i < m_currentEntity;i++)
    {
        sf::Rect<Real> rect(m_entities[i]->GetPosition().x, m_entities[i]->GetPosition().y, 
            m_entities[i]->GetPosition().x + m_entities[i]->m_halfWidth * (Real)2.0, m_entities[i]->GetPosition().y + m_entities[i]->m_halfHeight * (Real)2.0);
        if(PointIsInside(mousePos, rect))
            return m_entities[i];
    }

    return 0;
}
