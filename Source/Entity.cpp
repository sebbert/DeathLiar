#include "Entity.h"

bool Entity::SetSprite(const char *fileName)
{
    sf::Image image;
    if(!image.LoadFromFile(fileName))
    {
        return false;
    }

    m_sprite.SetImage(image);
}

void Entity::SetSprite(sf::Image &image)
{
    m_sprite.SetImage(image);
}