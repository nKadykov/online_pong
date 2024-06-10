#include "game.h"

Game::Game() {
    m_back_texture.loadFromFile("assets/back.jpg");
    m_back_sprite.setTexture(m_back_texture);
}

void Game::setState(GameState state) {
    m_state = state;
}

GameState Game::getState() const {
    return m_state;
}

void Game::Start(sf::RenderWindow& window) {
    window.draw(m_back_sprite);
}