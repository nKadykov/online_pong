#include "game.h"
#include "paddle.h"
#include "ball.h"
#include <iostream>

Game::Game() {
    if(!m_back_texture.loadFromFile("assets/back.jpg"))
        exit(1);
    m_back_sprite.setTexture(m_back_texture);
    if(!m_font.loadFromFile("assets/impactregular.ttf"))
        exit(1);
    m_score_text.setFont(m_font);
    m_score_text.setPosition(600, 10);
    m_score_text.setOutlineColor(sf::Color::Black);
    m_score_text.setOutlineThickness(2);
    m_score_text.setCharacterSize(40);
}

void Game::setState(GameState state) {
    m_state = state;
}

GameState Game::getState() const {
    return m_state;
}

void Game::start(sf::RenderWindow& window, std::string host, unsigned short port) {
    Paddle paddle1(2, 300);
    Paddle paddle2(1266, 300);
    Ball ball(1280.0f / 2, 720.0f / 2);
    sf::Clock clock;
    sf::Time dt;
    sf::Event event;
    Client client(host, port);
    client.start();

    while(window.isOpen()) {
        dt = clock.restart();
        while(window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                window.close();

        PositionState game_state = {
            ball.getPosition(),
            paddle1.getPosition(),
            paddle2.getPosition(),
            m_score_left,
            m_score_right
        };
        client.setGameState(game_state);
        PositionState server_state = client.getGameState();
        ball.setPosition(server_state.ball);
        paddle1.setPosition(server_state.paddle1);
        paddle2.setPosition(server_state.paddle2);
        m_score_left = server_state.score1;
        m_score_right = server_state.score2;

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
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            m_state = GameState::ON;
        }

        if(ball.getGlobalBounds().intersects(paddle1.getGlobalBounds()) && ball.getGlobalBounds().top + ball.getGlobalBounds().height / 2 >= paddle1.getGlobalBounds().top && ball.getGlobalBounds().top + ball.getGlobalBounds().height / 2 <= paddle1.getGlobalBounds().top + paddle1.getGlobalBounds().height)
            ball.hitBall();

        if(ball.getGlobalBounds().intersects(paddle2.getGlobalBounds()) && ball.getGlobalBounds().top + ball.getGlobalBounds().height / 2 >= paddle2.getGlobalBounds().top && ball.getGlobalBounds().top + ball.getGlobalBounds().height / 2 <= paddle2.getGlobalBounds().top + paddle2.getGlobalBounds().height)
            ball.hitBall();

        if(ball.getGlobalBounds().top < 0 || ball.getGlobalBounds().top > 690)
            ball.bounceSides();
        
        if(ball.getGlobalBounds().left < 0) {
            ball.bounceLeft();
            m_score_right++;
        }

        if(ball.getGlobalBounds().left > 1250) {
            ball.bounceRight();
            m_score_left++;
        }

        m_score_text.setString(std::to_string(m_score_left) + " : " + std::to_string(m_score_right));

        window.clear();
        if(m_state == GameState::ON) {
            paddle1.update(dt);
            paddle2.update(dt);
            ball.update(dt);
        }
        window.draw(m_back_sprite);
        window.draw(paddle1.getShape());
        window.draw(paddle2.getShape());
        window.draw(ball.getShape());
        window.draw(m_score_text);
        window.display();
    }
    client.stop();
}