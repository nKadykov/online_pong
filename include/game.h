#pragma once
#include "game_client.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class GameState {ON, LOSE, MENU, PAUSE};

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

    void start(sf::RenderWindow&, std::string, unsigned short);
private:
    sf::Texture m_back_texture;
    sf::Sprite m_back_sprite;
    GameState m_state = GameState::PAUSE;
    int m_score_left = 0;
    int m_score_right = 0;
    sf::Font m_font;
    sf::Text m_score_text;
    bool if_on = false;
};