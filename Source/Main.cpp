#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    std::cout << "Opening a window..." << std::endl;

    sf::RenderWindow app(sf::VideoMode(800, 600, 32), "AI Fun");
    app.SetFramerateLimit(30);

    bool running = true;
    while(running)
    {
        sf::Event event;
        while(app.GetEvent(event))
        {
            if(event.Type == sf::Event::Closed)
            {
                running = false;
            }
        }
        
        app.Clear(sf::Color(255, 255, 255));
        app.Display();
    }

    return EXIT_SUCCESS;
}