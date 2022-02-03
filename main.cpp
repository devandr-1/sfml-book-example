#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "hero.h"
#include "enemy.h"
#include "orion.h"

sf::Vector2f viewSize(1024, 768);
sf::VideoMode vm(viewSize.x, viewSize.y);

sf::RenderWindow window(vm, "Hello SFML", sf::Style::Default);

sf::Texture skyTexture, bgTexture;
sf::Sprite skySprite, bgSprite;

Hero hero;
std::vector<Enemy*> enemies;
std::vector<Orion*> orions;

float currentTime;
float prevTime = 0.f;

int score = 0;
bool gameOver = true;

sf::Font headingFont;
sf::Text headingText;

sf::Font scoreFont;
sf::Text scoreText;

sf::Text tutorialText;

sf::Music bgMusic;

sf::SoundBuffer fireBuffer;
sf::SoundBuffer hitBuffer;
sf::SoundBuffer gameOverBuffer;

sf::Sound fireSound(fireBuffer);
sf::Sound hitSound(hitBuffer);
sf::Sound gameOverSound(gameOverBuffer);

void spawnEnemy();
void shoot();
bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2);
void reset();

void init()
{
    skyTexture.loadFromFile("assets/sky.png");
    skySprite.setTexture(skyTexture);

    bgTexture.loadFromFile("assets/background.png");
    bgSprite.setTexture(bgTexture);

    hero.init("assets/player_stand.png", sf::Vector2f(viewSize.x * .25f, viewSize.y * .5f), 200.f);

    srand((int)time(0));

    headingFont.loadFromFile("assets/fonts/SunnyspellsRegular-MV9ze.otf");
    headingText.setFont(headingFont);
    headingText.setString("Wrath of zombies");
    headingText.setCharacterSize(84);
    headingText.setFillColor(sf::Color::Red);

    sf::FloatRect headingBounds = headingText.getLocalBounds();
    headingText.setOrigin(headingBounds.width / 2, headingBounds.height / 2);
    headingText.setPosition(sf::Vector2f(viewSize.x * .5f, viewSize.y * .1f));

    scoreFont.loadFromFile("assets/fonts/Geometria-Medium.ttf");
    scoreText.setFont(scoreFont);
    scoreText.setString("Score: 0");
    scoreText.setCharacterSize(45);
    scoreText.setFillColor(sf::Color::Red);

    sf::FloatRect scoreBounds = scoreText.getLocalBounds();
    scoreText.setOrigin(scoreBounds.width / 2, scoreBounds.height / 2);
    scoreText.setPosition(sf::Vector2f(viewSize.x * .5f, viewSize.y * .1f));

    tutorialText.setFont(scoreFont);
    tutorialText.setString("Press Enter to Fire and Start Game, Space to Jump");
    tutorialText.setCharacterSize(35);
    tutorialText.setFillColor(sf::Color::Red);

    sf::FloatRect tutorialBounds = tutorialText.getLocalBounds();
    tutorialText.setOrigin(tutorialBounds.width / 2, tutorialBounds.height / 2);
    tutorialText.setPosition(sf::Vector2f(viewSize.x * .5f, viewSize.y * .2f));

    bgMusic.openFromFile("assets/sounds/sound-track.wav");
    bgMusic.setLoop(true);
    bgMusic.play();

    hitBuffer.loadFromFile("assets/sounds/hit.wav");
    fireBuffer.loadFromFile("assets/sounds/knife-throw.wav");
    gameOverBuffer.loadFromFile("assets/sounds/game-over.wav");
}

void updateInput()
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                hero.jump(750.f);
            }
            if (event.key.code == sf::Keyboard::Enter) {
                if (gameOver) {
                    gameOver = false;
                    reset();
                } else {
                    shoot();
                }
            }
        }
    }
}

void update(float dt)
{
    hero.update(dt);

    currentTime += dt;
    if (currentTime >= prevTime + 1.125f) {
        spawnEnemy();
        prevTime = currentTime;
    }

    for (int i = 0; i < enemies.size(); i++) {
        Enemy *enemy = enemies[i];
        enemy->update(dt);

        if (enemy->getSprite().getPosition().x < 0) {
            enemies.erase(enemies.begin() + i);
            delete(enemy);
            gameOver = true;
            gameOverSound.play();
        }
    }

    for (int i = 0; i < orions.size(); i++) {
        Orion* orion = orions[i];
        orion->update(dt);

        if (orion->getSprite().getPosition().x > viewSize.x) {
            orions.erase(orions.begin() + i);
            delete(orion);
        }
    }

    for (int i = 0; i < orions.size(); i++) {
        for (int j = 0; j < enemies.size(); j++) {
            Orion* orion = orions[i];
            Enemy* enemy = enemies[j];

            if (checkCollision(orion->getSprite(), enemy->getSprite())) {
                hitSound.play();
                score++;

                std::string finalScore = "Score: " + std::to_string(score);
                scoreText.setString(finalScore);
                sf::FloatRect scoreBounds = scoreText.getLocalBounds();
                scoreText.setOrigin(scoreBounds.width / 2, scoreBounds.height / 2);
                scoreText.setPosition(sf::Vector2f(viewSize.x * .5f, viewSize.y * .1f));

                orions.erase(orions.begin() + i);
                delete(orion);

                enemies.erase(enemies.begin() + j);
                delete(enemy);
            }
        }
    }
}

void draw()
{
    window.draw(skySprite);
    window.draw(bgSprite);
    window.draw(hero.getSprite());

    for (Enemy* enemy : enemies) {
        window.draw(enemy->getSprite());
    }

    for (Orion* orion : orions) {
        window.draw(orion->getSprite());
    }

    if (gameOver) {
        window.draw(headingText);
        window.draw(tutorialText);
    } else {
        window.draw(scoreText);
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

        if (!gameOver) {
            update(dt.asSeconds());
        }

        window.clear(sf::Color::Red);
        draw();
        window.display();

        
    }

    return 0;
}

void spawnEnemy()
{
    int randLock = rand() % 3;

    sf::Vector2f enemyPos;
    float speed;

    switch (randLock)
    {
        case 0: {
            enemyPos = sf::Vector2f(viewSize.x, viewSize.y * .75f);
            speed = -400;
        }; break;
        case 1: {
            enemyPos = sf::Vector2f(viewSize.x, viewSize.y * .6f);
            speed = -550;
        }; break;
        case 2: {
            enemyPos = sf::Vector2f(viewSize.x, viewSize.y * .4f);
            speed = -650;
        }; break;
        default: {
            printf("Incorect y value\n");
        }; return;
    }

    Enemy* enemy = new Enemy();
    enemy->init("assets/zombie_skid.png", enemyPos, speed);

    enemies.push_back(enemy);
}

void shoot()
{
    Orion* orion = new Orion();
    orion->init("assets/orion.png", hero.getSprite().getPosition(), 400.f);

    orions.push_back(orion);

    fireSound.play();
}


bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2)
{
    sf::FloatRect shape1 = sprite1.getGlobalBounds();
    sf::FloatRect shape2 = sprite2.getGlobalBounds();

    return shape1.intersects(shape2);
}

void reset()
{
    score = 0;
    currentTime = 0.f;
    prevTime = 0.f;
    scoreText.setString("Score: 0");

    for (Enemy* enemy : enemies) {
        delete(enemy);
    }

    for (Orion* orion : orions) {
        delete(orion);
    }

    enemies.clear();
    orions.clear();
}