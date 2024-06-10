#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class GameState {ON, LOSE, MENU};

class Game {
public:
    Game();
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;
    ~Game() = default;

    void setState(GameState);
    
    GameState getState() const;

    void Start(sf::RenderWindow&);
private:
    sf::Texture m_back_texture;
    sf::Sprite m_back_sprite;
    GameState m_state = GameState::ON;
    int score_left = 0;
    int score_right = 0;
};