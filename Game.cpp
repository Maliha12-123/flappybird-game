#include "Game.h"
#include "Globals.h"
#include <cstdlib>
#include <iostream>

Game::Game(sf::RenderWindow& window)
    : win(window), score(0) {

    // Background
    bgTexture.loadFromFile(
        "assets/Flappy_Bird_assets by kosresetr55/Game Objects/background-day.png");
    bgSprite.setTexture(bgTexture);
    bgSprite.setScale(
        static_cast<float>(WIN_WIDTH) / bgTexture.getSize().x,
        static_cast<float>(WIN_HEIGHT) / bgTexture.getSize().y
    );

    // Game Over
    gameOverTexture.loadFromFile(
        "assets/Flappy_Bird_assets by kosresetr55/UI/gameover.png");
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition(
        WIN_WIDTH / 2.f - gameOverTexture.getSize().x / 2.f,
        WIN_HEIGHT / 2.f - 200.f
    );

    // Scoreboard
    scoreBoardTexture.loadFromFile(
        "assets/Flappy_Bird_assets by kosresetr55/UI/message.png");
    scoreBoardSprite.setTexture(scoreBoardTexture);
    scoreBoardSprite.setPosition(
        WIN_WIDTH / 2.f - scoreBoardTexture.getSize().x / 2.f,
        WIN_HEIGHT / 2.f - scoreBoardTexture.getSize().y / 2.f
    );

    // Numbers
    for (int i = 0; i < 10; ++i) {
        numberTextures[i].loadFromFile(
            "assets/Flappy_Bird_assets by kosresetr55/UI/Numbers/" +
            std::to_string(i) + ".png"
        );
    }

    states.push(GameState::PLAYING);
}

void Game::run() {
    while (win.isOpen()) {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event e;
    while (win.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            win.close();

        if (e.type == sf::Event::KeyPressed &&
            e.key.code == sf::Keyboard::Space) {

            if (states.top() == GameState::PLAYING)
                bird.jump();
            else
                reset();
        }
    }
}

void Game::update(float dt) {
    if (states.top() != GameState::PLAYING)
        return;

    bird.update(dt);

    // Spawn pipes
    if (pipesQueue.empty() ||
        pipesQueue.back()->getX() < 300.f) {

        float gapY = static_cast<float>(std::rand() % 300 + 150);

        pipesQueue.push(
            std::make_unique<Pipe>(
                static_cast<float>(WIN_WIDTH),
                gapY
            )
        );
    }

    size_t size = pipesQueue.size();

    for (size_t i = 0; i < size; ++i) {
        auto pipe = std::move(pipesQueue.front());
        pipesQueue.pop();

        pipe->update(dt);

        // Score check
        float pipeCenter =
            pipe->getX() + pipe->topBounds().width / 2.f;

        float birdCenter =
            bird.getBounds().left +
            bird.getBounds().width / 2.f;

        if (!pipe->passed && birdCenter > pipeCenter) {
            ++score;
            pipe->passed = true;
        }

        // Collision
        if (bird.getBounds().intersects(pipe->topBounds()) ||
            bird.getBounds().intersects(pipe->bottomBounds())) {
            states.push(GameState::GAMEOVER);
        }

        if (!pipe->isOffScreen())
            pipesQueue.push(std::move(pipe));
    }
}

void Game::updateScoreSprites() {
    scoreSprites.clear();
    std::string s = std::to_string(score);

    float x, y;

    if (states.top() == GameState::PLAYING) {
        x = WIN_WIDTH / 2.f - (s.size() * 24.f) / 2.f;
        y = 30.f;
    }
    else {
        x = scoreBoardSprite.getPosition().x + 100.f;
        y = scoreBoardSprite.getPosition().y + 90.f;
    }

    for (char c : s) {
        sf::Sprite sp;
        sp.setTexture(numberTextures[c - '0']);
        sp.setScale(0.5f, 0.5f);
        sp.setPosition(x, y);
        scoreSprites.push_back(sp);
        x += 24.f;
    }
}

void Game::render() {
    win.clear();

    win.draw(bgSprite);

    // ✅ SAFE drawing of pipes (no copying unique_ptr)
    size_t size = pipesQueue.size();
    for (size_t i = 0; i < size; ++i) {
        auto pipe = std::move(pipesQueue.front());
        pipesQueue.pop();

        pipe->draw(win);

        pipesQueue.push(std::move(pipe));
    }

    bird.draw(win);

    updateScoreSprites();
    for (auto& s : scoreSprites)
        win.draw(s);

    if (states.top() == GameState::GAMEOVER) {
        win.draw(gameOverSprite);
        win.draw(scoreBoardSprite);
    }

    win.display();
}


void Game::reset() {
    while (!pipesQueue.empty())
        pipesQueue.pop();

    bird.reset();
    score = 0;

    while (!states.empty())
        states.pop();

    states.push(GameState::PLAYING);
}
