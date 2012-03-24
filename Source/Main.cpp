#include "World.h"
#include "Entity.h"
#include "Enemy.h" 
#include <iostream>

int main()
{
    std::cout << "Opening a window..." << std::endl;

    gWorld.Init();

    while(gWorld.GameOn())
    {
        gWorld.Update();
    }

    return EXIT_SUCCESS;
}