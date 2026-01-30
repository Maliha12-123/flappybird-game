#include "Bird.h"
#include <iostream>

Bird::Bird() {
    if (!texture.loadFromFile("assets/Flappy_Bird_assets by kosresetr55/Game Objects/yellowbird-downflap.png"))
        std::cout << "Failed to load bird texture\n";

    sprite.setTexture(texture);
    sprite.setPosition(100.f, WIN_HEIGHT / 2.f);
    yVelocity = 0.f;
}

void Bird::update(float dt) {
    yVelocity += gravity * dt;
    sprite.move(0.f, yVelocity * dt);

    if (sprite.getPosition().y < 0.f)
        sprite.setPosition(sprite.getPosition().x, 0.f);

    if (sprite.getPosition().y > WIN_HEIGHT - sprite.getGlobalBounds().height)
        sprite.setPosition(sprite.getPosition().x, WIN_HEIGHT - sprite.getGlobalBounds().height);
}

void Bird::jump() {
    yVelocity = jumpForce;
}

void Bird::reset() {
    sprite.setPosition(100.f, WIN_HEIGHT / 2.f);
    yVelocity = 0.f;
}

void Bird::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Bird::getBounds() {
    return sprite.getGlobalBounds();
}
