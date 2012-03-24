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