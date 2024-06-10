#include "game.h"
#include "paddle.h"

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
    Paddle paddle1(2, 300);
    Paddle paddle2(1266, 300);
    sf::Clock clock;
    sf::Time dt;
    sf::Event event;
    window.draw(m_back_sprite);
    while(window.isOpen()) {
        dt = clock.restart();
        while(window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                window.close();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            paddle1.moveDown();
        else
            paddle1.stopDown();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            paddle1.moveUp();
        else
            paddle1.stopUp();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            paddle2.moveDown();
        else
            paddle2.stopDown();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            paddle2.moveUp();
        else
            paddle2.stopUp();

        window.clear();
        paddle1.update(dt);
        paddle2.update(dt);
        window.draw(m_back_sprite);
        window.draw(paddle1.getShape());
        window.draw(paddle2.getShape());
        window.display();
    }
}