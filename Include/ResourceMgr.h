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