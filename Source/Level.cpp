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

#include "Level.h"
#include "World.h"
#include "ResourceMgr.h"
#include "Wall.h"

Level::~Level()
{
    Destroy();
}

void Level::Init(const char *levelName)
{
    std::string fileName;
    int lenLevelName = strlen(levelName);
    fileName.resize(19 + lenLevelName * 2);

    fileName = "Media/Levels/";
    fileName += levelName;
    m_path = fileName;
    fileName += "/";
    fileName += levelName;

    m_levelWidth = gWorld.GetParams().m_zoneWidth * 3;
    m_levelHeight = gWorld.GetParams().m_zoneHeight * 3;

    m_gridSize.x = 64;
    m_gridSize.y = 64;
    m_gridExtentX = (unsigned)m_levelWidth / (unsigned)m_gridSize.x;
    m_gridExtentY = (unsigned)m_levelHeight / (unsigned)m_gridSize.y;

    for(int i = 0;i < 3;i++)
    {
        for(int j = 0;j < 3;j++)
        {
            char idInChar[6] = {'1', '\0', 'p', 'n', 'g', '\0'};
#ifdef WIN32
            _itoa_s(i * 3 + j, idInChar, 10);
#elif defined(__APPLE__)
            sprintf(idInChar, "%i", i * 3 + j);
#else
            itoa(i * 3 + j, idInChar, 10);
#endif
            idInChar[1] = '.';
            fileName.replace(14 + lenLevelName * 2, 5, idInChar); 

            //sf::Image& image = *gResourceMgr.GetImage(fileName.c_str());
            sf::Image& image = *gResourceMgr.GetImage("Media/Levels/Graveyard/Graveyard0.png");
            image.SetSmooth(false);

            if(image.GetWidth() != gWorld.GetParams().m_zoneWidth || image.GetHeight() != gWorld.GetParams().m_zoneHeight)
            {
                std::cout << "Size of zone, differs from size of image.\n";
            }

            m_zones[i * 3 + j].SetImage(image);
            m_zonePositions[i * 3 + j].Set(j * (Real)gWorld.GetParams().m_zoneWidth, i * (Real)gWorld.GetParams().m_zoneHeight);
        }
    }

    LoadLevelInfo();
}

void Level::Destroy()
{
    for(EntityIter iter = m_entities.begin();iter != m_entities.end();++iter)
    {
        if(iter->second)
        {
            delete iter->second;
            iter->second = 0;
        }
    }
}

void Level::Draw()
{
    int zones[4];
    zones[0] = -1;
    zones[1] = -1;
    zones[2] = -1;
    zones[3] = -1;

    Vec2D oppositPos = gWorld.GetCameraPos().Opposite();
 
    Vec2D point = oppositPos;
    zones[0] = GetZoneFromPoint(point);

    point.x += gWorld.GetParams().m_windowWidth;
    zones[1] = GetZoneFromPoint(point);

    point.y += gWorld.GetParams().m_windowHeight;
    zones[2] = GetZoneFromPoint(point);

    point = oppositPos;
    point.y += gWorld.GetParams().m_windowHeight;
    zones[3] = GetZoneFromPoint(point);

    //Make sure a zone is not rendered twice, or a zone does not exist.
    for(int i = 0;i < 4;i++)
    {
        if(zones[i] > 8)
        {
            zones[i] = -1;
            continue;
        }
        for(int j = 0;j < 4;j++)
        {
            if(zones[i] == zones[j] && i != j)
            {
                zones[i] = -1;
            }
        }
    }

    for(int i = 0;i < 4;i++)
    {
        if(zones[i] >= 0)
        {
            point = gWorld.m_camera.m_position;
            point += m_zonePositions[zones[i]];
            
            m_zones[zones[i]].SetPosition(point.x, point.y);
            gWindow->Draw(m_zones[zones[i]]);
        }
    }
    
    for(EntityIter iter = m_entities.begin();iter != m_entities.end();++iter)
    {
        iter->second->Draw(gWorld.GetFrameTime());
    }
}

bool Level::CollisionWithWalls(Entity *entity)
{
    for(EntityIter iter = m_entities.begin();iter != m_entities.end();++iter)
    {
        Wall *pWall = static_cast<Wall*>(iter->second);
        //Vec2D between = pWall->m_endPoint - pWall->m_startPoint;
       
        if(GetZoneFromPoint(pWall->GetPosition()) == GetZoneFromPoint(entity->GetPosition()))
        {     
           /* Vec2D toWall = pos - entity->GetPosition();
            Real dist = toWall.Magnitude();*/
        
            /*
            between.Normalize();

            Real rad = AngleBetweenPoints(between, Vec2D(0,0)); //+ HALF_PI;
        
            Vec2D newPos = toWall;
            newPos.Rotate((PI - rad) * 0.5);
            //size.Rotate(rad);

            newPos.Normalize();
            Real distCircle = sin(rad) * dist;
            newPos *= distCircle;
            newPos += entity->GetPosition();*/

            Vec2D size(pWall->m_halfWidth, pWall->m_halfHeight);
            if(RectangleIntersectCircle(pWall->GetPosition(), size, entity->GetPosition(), entity->m_halfWidth - 2))
            {
                return true;
            }
        }
    }
    
    return false;
}

int Level::GetZoneFromPoint(const Vec2D &point)
{
    Vec2D square;
    square.x = point.x / gWorld.GetParams().m_zoneWidth;
    square.y = point.y / gWorld.GetParams().m_zoneHeight;

    return (unsigned)(square.x) + 3*(unsigned)(square.y);
}

int Level::GetCellFromPoint(const Vec2D &point)
{
    Vec2D square;
    square.x = point.x / m_gridSize.x;
    square.y = point.y / m_gridSize.y;

    return (unsigned)(square.x) + m_gridExtentX*(unsigned)(square.y);
}

void Level::AddEntity(int cell, Entity *entity)
{
    EntityIter found = m_entities.find(cell);
    if(found != m_entities.end())
    {
        std::cout << "Cell is occupied.\n";
    }
    m_entities[cell] = entity;
}

bool Level::LoadLevelInfo()
{
    std::ifstream file((m_path + "/level.dat").c_str(), std::ios::binary);
    if(!file.is_open())
    {
        /*std::cout << "Could not find level.dat. A team of highly trained monkeys has been dispatched to deal with this situation. If you see them give them this fucking code: ";
        for(int i = 0;i < 100;i++)
        {
            std::cout << sf::Randomizer::Random(48, 90);
        }

        std::cout << std::endl;*/

        return false;
    }

    char numEntities;
    file.read((char*)&numEntities, sizeof(char));
    
    for(int i = 0;i < numEntities;i++)
    {
        char type;
        file.read(&type, sizeof(char));

        Vec2D position;
        Real rotation;
        file.read((char*)&position, sizeof(Vec2D));
        file.read((char*)&rotation, sizeof(Real));

        Entity *entity = 0;
        switch(type)
        {
        case ENTITY_WALL:
            entity = new Wall;
            break;
        case ENTITY_SPAWN_POINT:
            entity = new EnemySpawnPoint;
            break;
        default:
            std::cout << "Unsupported type of entity in level.\n";
        };

        if(entity)
        {
            entity->SetPosition(position);
            entity->GetSprite().SetRotation(rotation);

            m_entities[GetCellFromPoint(position)] = entity;
        }
    }

    file.close();

    return true;
}

void Level::SaveLevelInfo()
{
    std::ofstream file((m_path + "/level.dat").c_str(), std::ios::binary);
    if(!file.is_open())
    {
        std::cout << "Failed to save level. Check if level is open in another instance.\n";
        return;
    }

    char numberOfEntities = m_entities.size();
    file.write((const char*)&numberOfEntities, sizeof(char));
    for(EntityIter iter = m_entities.begin();iter != m_entities.end();++iter)
    {
        char type = (char)iter->second->GetType();
        Real rotation = iter->second->GetRotation();

        file.write((char*)&type, sizeof(char));
        file.write((char*)&iter->second->GetPosition(), sizeof(Vec2D));
        file.write((char*)&rotation, sizeof(Real));
    }

    file.close();
}

Entity *Level::GetEntityFromCell(int cell)
{
    EntityIter found = m_entities.find(cell);
    if(found != m_entities.end())
    {
        return found->second;
    }

    return 0;
}

void Level::RemoveEntityFromCell(int cell)
{
    EntityIter found = m_entities.find(cell);
    if(found != m_entities.end())
    {
        m_entities.erase(found);
    }
}

Vec2D Level::GetCenterOfCell(int cell)
{
    //return (unsigned)(square.x) + m_gridExtentX*(unsigned)(square.y);
    Real offsetX = (Real)cell - (Real)m_gridExtentX;
    return Vec2D(m_gridSize.x * (offsetX < 0 ? cell : offsetX) + (m_gridSize.x * (Real)0.5), m_gridSize.y * (unsigned)(cell / m_gridExtentX) + (m_gridSize.y * 0.5));
}

Vec2D Level::SnapToCenter(const Vec2D &point)
{
    Vec2D square;
    square.x = point.x / m_gridSize.x;
    square.y = point.y / m_gridSize.y;

    return Vec2D((unsigned)square.x * m_gridSize.x, (unsigned)square.y * m_gridSize.y);
}