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

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

/**
 * Resource manager controls which resources to be loaded or not.
 */
class ResourceMgr
{
public:
    sf::Image *GetImage(const char *fileName);

    static ResourceMgr &Instance()
    {
        static ResourceMgr instance;
        return instance;
    }
private:
    ResourceMgr() {}
    ResourceMgr(const ResourceMgr&) {}
    ResourceMgr operator =(const ResourceMgr&) {}

    typedef std::map<std::string, sf::Image>::iterator ImageIter;
    std::map<std::string, sf::Image> m_imageData;///< Hash map of strings and images.
};

#define gResourceMgr ResourceMgr::Instance()

#endif