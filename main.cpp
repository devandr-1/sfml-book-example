#include <iostream>
#include <SFML/Graphics.hpp>
#include "hero.h"

sf::Vector2f viewSize(1024, 768);
sf::VideoMode vm(viewSize.x, viewSize.y);

sf::RenderWindow window(vm, "Hello SFML", sf::Style::Default);

sf::Texture skyTexture, bgTexture;
sf::Sprite skySprite, bgSprite;

Hero hero;

void draw()
{
    window.draw(skySprite);
    window.draw(bgSprite);
    window.draw(hero.getSprite());
}

void init()
{
    skyTexture.loadFromFile("assets/sky.png");
    skySprite.setTexture(skyTexture);

    bgTexture.loadFromFile("assets/background.png");
    bgSprite.setTexture(bgTexture);

    hero.init("assets/player_stand.png", sf::Vector2f(viewSize.x * .25f, viewSize.y * .5f), 200.f);
}

void updateInput()
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.key.code == sf::Keyboard::Space) {
            if (event.type == sf::Event::KeyPressed) {
                hero.jump(750.f);
            }
        }
    }
}

void update(float dt)
{
    hero.update(dt);
}

int main()
{
    sf::Clock clock;

    init();

    while (window.isOpen())
    {
        updateInput();

        sf::Time dt = clock.restart();
        update(dt.asSeconds());

        window.clear(sf::Color::Red);
        draw();
        window.display();

        
    }

    return 0;
}