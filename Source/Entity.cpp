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

Entity::Entity()
{
    m_id = GetNextID();
}

bool Entity::SetSprite(const char *fileName)
{
    sf::Image *image = gResourceMgr.GetImage(fileName);
    if(image != 0)
    {
        m_sprite.SetImage(*image);
    }
    
    return (bool)image;
}

void Entity::SetSprite(sf::Image &image)
{
    m_sprite.SetImage(image);
}

void Entity::Draw(Real duration)
{
    Update(duration);

    gWindow->Draw(m_sprite);
}

void Entity::Update(Real duration)
{
}