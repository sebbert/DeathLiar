#include "Level.h"
#include "World.h"
#include "ResourceMgr.h"

void Level::Init()
{
    for(int i = 0;i < 3;i++)
    {
        for(int j = 0;j < 3;j++)
        {
            m_zones[i * 3 + j].SetImage(*gResourceMgr.GetImage("Media/part1.png"));
            m_zonePositions[i * 3 + j].Set(j * 1024, i * 1024);
        }
    }
}

void Level::SetPosition(const Vec2D &pos)
{
    m_position = pos;
}

void Level::Draw()
{
    int zones[4];
    zones[0] = -1;
    zones[1] = -1;
    zones[2] = -1;
    zones[3] = -1;

    Vec2D oppositPos = m_position.Opposite();
 
    Vec2D point = oppositPos;
    zones[0] = GetZoneFromPoint(point);

    point.x += WINDOW_WIDTH;
    zones[1] = GetZoneFromPoint(point);

    point.y += WINDOW_HEIGHT;
    zones[2] = GetZoneFromPoint(point);

    point = oppositPos;
    point.y += WINDOW_HEIGHT;
    zones[3] = GetZoneFromPoint(point);

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
            point = m_position;
            point += m_zonePositions[zones[i]];

            m_zones[zones[i]].SetPosition(point.x, point.y);
            gWindow->Draw(m_zones[zones[i]]);
        }
    }
}

int Level::GetZoneFromPoint(const Vec2D &point)
{
    Vec2D square;
    square.x = point.x / 1024;
    square.y = point.y / 1024;

    return (unsigned)(square.x) + 3*(unsigned)(square.y);
}