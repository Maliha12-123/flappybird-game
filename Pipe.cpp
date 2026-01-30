#include "Pipe.h"
#include "Globals.h"

Pipe::Pipe(float x, float gapY) : passed(false) // ✅ Initialize passed as false
{
    tex.loadFromFile("assets/Flappy_Bird_assets by kosresetr55/Game Objects/pipe-green.png"); // CHANGE PATH
    top.setTexture(tex);
    bottom.setTexture(tex);

    top.setScale(1.f, -1.f); // flip top pipe
    top.setPosition(x, gapY - PIPE_GAP);
    bottom.setPosition(x, gapY + PIPE_GAP);
}

void Pipe::update(float dt) {
    top.move(-PIPE_SPEED * dt, 0.f);
    bottom.move(-PIPE_SPEED * dt, 0.f);
}

void Pipe::draw(sf::RenderWindow& win) {
    win.draw(top);
    win.draw(bottom);
}

bool Pipe::isOffScreen() const {
    return top.getPosition().x < -100.f;
}

sf::FloatRect Pipe::topBounds() const {
    return top.getGlobalBounds();
}

sf::FloatRect Pipe::bottomBounds() const {
    return bottom.getGlobalBounds();
}

float Pipe::getX() const {
    return top.getPosition().x;
}
