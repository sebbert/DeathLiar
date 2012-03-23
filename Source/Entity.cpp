#include "Entity.h"
#include "ResourceMgr.h"

bool Entity::SetSprite(const char *fileName)
{
    sf::Image *image = gResourceMgr.GetImage(fileName);
    if(image != 0)
    {
        m_sprite.SetImage(*image);
    }

    return image;
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