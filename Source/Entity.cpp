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

#include "Entity.h"
#include "ResourceMgr.h"
#include "World.h"

sf::Uint16 Entity::sNextID = 0;
std::map<sf::Uint16, Entity*> Entity::m_entities;

Entity::Entity()
{
    m_id = GetNextID();
    AddEntity(m_id, this);
}

bool Entity::SetSprite(const char *fileName)
{
    sf::Image *image = gResourceMgr.GetImage(fileName);
    if(image != 0)
    {
        m_sprite.SetImage(*image);
        m_sprite.SetCenter((Real)image->GetWidth() * (Real)0.5, (Real)image->GetHeight() * (Real)0.5);
        m_halfWidth = m_sprite.GetImage()->GetWidth() * (Real)0.5;
        m_halfHeight = m_sprite.GetImage()->GetHeight() * (Real)0.5;
    }

    return image ? true : false;
}

void Entity::SetSprite(sf::Image &image)
{
    m_sprite.SetImage(image);
    m_halfWidth = m_sprite.GetImage()->GetWidth() * (Real)0.5;
    m_halfHeight = m_sprite.GetImage()->GetHeight() * (Real)0.5;
}

void Entity::Draw(Real duration)
{
    Update(duration);

    //Transform word coords to "clip" coords.
    Vec2D finalPos = m_position + gWorld.m_camera.m_position;
    m_sprite.SetPosition(finalPos.x, finalPos.y);
    
    //Don't draw sprite if out of screen.
    if(finalPos.x + m_halfWidth < 0 || finalPos.x - m_halfWidth > gWorld.GetParams().m_windowWidth 
        || finalPos.y + m_halfHeight < 0 || finalPos.y - m_halfHeight > gWorld.GetParams().m_windowHeight)
    {
        return;
    }
    gWindow->Draw(m_sprite);
}

void Entity::SetPosition(const Vec2D &pos)
{
    m_position = pos;
}

void Entity::Update(Real duration)
{
}