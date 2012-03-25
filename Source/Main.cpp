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

#include "World.h"
#include "Entity.h"
#include "Enemy.h" 
#include <iostream>

int main()
{
    std::cout << "\n"
    "8888888b.                    888    888      888      d8b                  \n"
    "888  'Y88b                   888    888      888      Y8P                  \n"
    "888    888                   888    888      888                           \n"
    "888    888  .d88b.   8888b.  888888 88888b.  888      888  8888b.  888d888 \n"
    "888    888 d8P  Y8b     '88b 888    888 '88b 888      888     '88b 888P'   \n"
    "888    888 88888888 .d888888 888    888  888 888      888 .d888888 888     \n"
    "888  .d88P Y8b.     888  888 Y88b.  888  888 888      888 888  888 888     \n"
    "8888888P'   'Y8888  'Y888888  'Y888 888  888 88888888 888 'Y888888 888     \n"
    "\n"
    "Copyright © 2012 Emil Sandstø, Sebastian Reinhard \n\n";
    
    std::cout << "Opening a window..." << std::endl;

    gWorld.Init();

    while(gWorld.GameOn())
    {
        gWorld.Update();
    }

    return EXIT_SUCCESS;
}