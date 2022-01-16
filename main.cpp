#include <iostream>
#include <SFML/Graphics.hpp>

sf::Vector2f viewSize(1024, 768);
sf::VideoMode vm(viewSize.x, viewSize.y);

sf::RenderWindow window(vm, "Hello SFML", sf::Style::Default);

sf::Texture skyTexture, bgTexture;
sf::Sprite skySprite, bgSprite;

sf::Texture heroTexture;
sf::Sprite heroSprite;

sf::Vector2f playerPosition;
bool playerMoving = false;

void draw()
{
    window.draw(skySprite);
    window.draw(bgSprite);
    window.draw(heroSprite);
}

void init()
{
    skyTexture.loadFromFile("assets/sky.png");
    skySprite.setTexture(skyTexture);

    bgTexture.loadFromFile("assets/background.png");
    bgSprite.setTexture(bgTexture);

    heroTexture.loadFromFile("assets/player_stand.png");
    heroSprite.setTexture(heroTexture);
    heroSprite.setPosition(sf::Vector2f(viewSize.x / 2, viewSize.y / 2));
    heroSprite.setOrigin(heroTexture.getSize().x / 2, heroTexture.getSize().y / 2);
}

void updateInput()
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.key.code == sf::Keyboard::D) {
            playerMoving = event.type == sf::Event::KeyPressed;
        }
    }
}

void update(float dt)
{
    if (playerMoving) {
        heroSprite.move(100.f * dt, 0);
    }
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