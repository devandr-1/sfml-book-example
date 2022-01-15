#include <iostream>
#include <SFML/Graphics.hpp>

sf::Vector2f viewSize(1024, 768);
sf::VideoMode vm(viewSize.x, viewSize.y);

sf::RenderWindow window(vm, "Hello SFML", sf::Style::Default);

int main()
{
    sf::RectangleShape rect(sf::Vector2f(500.f, 300.f));
    rect.setFillColor(sf::Color::Yellow);
    rect.setPosition(viewSize.x / 2, viewSize.y / 2);
    rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));

    while (window.isOpen())
    {
        window.clear(sf::Color::Red);

        window.draw(rect);

        window.display();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}