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

    for(int i = 0;i < 3;i++)
    {
        for(int j = 0;j < 3;j++)
        {
            char idInChar[6] = {'1', '\0', 'p', 'n', 'g', '\0'};
#ifdef WIN32
            _itoa_s(i * 3 + j, idInChar, 10);
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

    std::ifstream file(m_path + "/level.dat", std::ios::binary);
    if(!file.is_open())
    {
        std::cout << "Could not find level.dat. A team of highly trained monkeys has been dispatched to deal with this situation. If you see them give them this fucking code: ";
        for(int i = 0;i < 100;i++)
        {
            std::cout << sf::Randomizer::Random(48, 90);
        }

        return;
    }

    file.read((char*)&m_numEntities, sizeof(char));
    m_entities = new Entity*[m_numEntities];
    
    for(int i = 0;i < m_numEntities;i++)
    {
        char type;
        file.read(&type, sizeof(char));
        if(type == ENTITY_WALL)
        {
            Vec2D startPoint, endPoint;
            file.read((char*)&startPoint, sizeof(Vec2D));
            file.read((char*)&endPoint, sizeof(Vec2D));
            m_entities[i] = new Wall(startPoint, endPoint);
        }
        else
        {
            Vec2D pos;
            Real rot;
            file.read((char*)&pos, sizeof(Vec2D));
            file.read((char*)&rot, sizeof(Real));
        }
    }

    file.close();
}

void Level::Destroy()
{
    if(m_entities != 0)
    {
        for(int i = 0;i < m_numEntities;i++)
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
    
    if(!gWorld.IsInLevelEditor())
    {
        for(int i = 0;i < m_numEntities;i++)
        {
            m_entities[i]->Draw(gWorld.GetFrameTime());
        }
    }
}

bool Level::CollisionWithWalls(Entity *entity)
{
    for(int i = 0;i < m_numEntities;i++)
    {
        Wall *pWall = static_cast<Wall*>(m_entities[i]);
        //Vec2D between = pWall->m_endPoint - pWall->m_startPoint;
        Vec2D size = pWall->m_endPoint - pWall->m_startPoint;
        Vec2D pos = pWall->m_startPoint + (size * 0.5);
       
        if(GetZoneFromPoint(pos + size) == GetZoneFromPoint(entity->GetPosition()))
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

            if(RectangleIntersectCircle(pos, size, entity->GetPosition(), entity->m_halfWidth))
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