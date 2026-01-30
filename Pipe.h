#pragma once
#include <SFML/Graphics.hpp>

class Pipe {
public:
    Pipe(float x, float gapY);

    void update(float dt);
    void draw(sf::RenderWindow& win);

    bool isOffScreen() const;
    sf::FloatRect topBounds() const;
    sf::FloatRect bottomBounds() const;
    float getX() const;

    bool passed;

private:
    sf::Texture tex;
    sf::Sprite top, bottom;
};
