#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <queue>
#include <memory>          // ✅ REQUIRED
#include <vector>
#include "Bird.h"
#include "Pipe.h"

enum class GameState { PLAYING, GAMEOVER };

class Game {
public:
    Game(sf::RenderWindow& window);
    void run();

private:
    sf::RenderWindow& win;
    sf::Clock clock;

    Bird bird;

    // ✅ MUST match Game.cpp
    std::queue<std::unique_ptr<Pipe>> pipesQueue;

    std::stack<GameState> states;

    // Background
    sf::Texture bgTexture;
    sf::Sprite bgSprite;

    // Game over
    sf::Texture gameOverTexture;
    sf::Sprite gameOverSprite;

    // Scoreboard
    sf::Texture scoreBoardTexture;
    sf::Sprite scoreBoardSprite;

    // Numbers
    sf::Texture numberTextures[10];
    std::vector<sf::Sprite> scoreSprites;

    int score;

    void processEvents();
    void update(float dt);
    void updateScoreSprites();
    void render();
    void reset();
};
