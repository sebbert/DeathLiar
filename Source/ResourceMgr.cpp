#include "ResourceMgr.h"
#include <cassert>

sf::Image *ResourceMgr::GetImage(const char *fileName)
{
    ImageIter iter = m_imageData.find(fileName);
    sf::Image *image = 0;
    if(iter == m_imageData.end())
    {
        image = &m_imageData[fileName];
        if(!image->LoadFromFile(fileName))
        {
            return 0;
        }
        
        image->SetSmooth(false);
    }
    else
    {
        image = &iter->second;
    }

    return image;
}