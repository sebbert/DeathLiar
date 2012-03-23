#include "World.h"
#include "Entity.h"
#include <iostream>

int main()
{
    std::cout << "Opening a window..." << std::endl;

    gWorld.Init();
    Entity entity;
    entity.SetSprite("");

    bool running = true;
    while(running)
    {
        sf::Event event;
        while(gWindow->GetEvent(event))
        {
            if(event.Type == sf::Event::Closed)
            {
                running = false;
            }
            if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape)
            {
                running = false;
            }
        }
        
        gWindow->Clear(sf::Color(255, 255, 255));
        
        gWindow->Display();
    }

    return EXIT_SUCCESS;
}