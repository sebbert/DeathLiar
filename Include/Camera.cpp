#include "Camera.h"
#include "Entity.h"
#include "World.h"

void Camera::FollowMe(Entity *entity, bool center)
{
    m_position = entity->GetPosition().Opposite();
    
    if(center)
    {
        m_position += gWorld.GetWindowCenter();
        
        Real camBorderX = -((Real)gWorld.GetLevel().m_levelWidth - (Real)gWorld.GetParams().m_windowWidth);
        Real camBorderY = -((Real)gWorld.GetLevel().m_levelHeight - (Real)gWorld.GetParams().m_windowHeight);

        if(-m_position.x < 0)
        {
            m_position.x = 0;
        }

        else if(m_position.x < camBorderX)
        {
            m_position.x = camBorderX;
        }
        
        if(-m_position.y < 0)
        {
            m_position.y = 0;
        }
        else if(m_position.y < camBorderY)
        {
            m_position.y = camBorderY;
        }
    }
}