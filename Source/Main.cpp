#include "World.h"
#include <iostream>

int main()
{
    std::cout << "Opening a window..." << std::endl;

    gWorld.Init();

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
        }
        
        gWindow->Clear(sf::Color(255, 255, 255));
        gWindow->Display();
    }

    return EXIT_SUCCESS;
}