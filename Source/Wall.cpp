#include "Wall.h"
#include "ResourceMgr.h"
#include "World.h"

Wall::Wall()
{
    std::string path = gWorld.GetLevel().GetPathToLevel();
    path += "/wall_tile.png";
    sf::Image &img = *gResourceMgr.GetImage(path.c_str());
    img.SetSmooth(false);
    SetSprite(img);
}