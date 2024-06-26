#include "paddle.h"

Paddle::Paddle(float start_x, float start_y) {
    m_position.x = start_x;
    m_position.y = start_y;
    m_shape.setSize(sf::Vector2f(12, 100));
    m_shape.setFillColor(sf::Color::Red);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(2);
    m_shape.setPosition(m_position);
}

void Paddle::setPosition(const sf::Vector2f& position) {
    m_shape.setPosition(position);
}

sf::RectangleShape Paddle::getShape() const {
    return m_shape;
}

sf::FloatRect Paddle::getGlobalBounds() const {
    return m_shape.getGlobalBounds();
}

sf::Vector2f Paddle::getPosition() const {
    return m_shape.getPosition();
}

void Paddle::moveDown() {
    m_moving_down = true;
}

void Paddle::moveUp() {
    m_moving_up = true;
}

void Paddle::stopDown() {
    m_moving_down = false;
}

void Paddle::stopUp() {
    m_moving_up = false;
}

void Paddle::update(sf::Time dt) {
    if(m_moving_down) {
        m_position.y += m_speed * dt.asSeconds();
    }
    if(m_moving_up) {
        m_position.y -= m_speed * dt.asSeconds();
    }
    if(m_position.y < 2) {
        m_position.y = 2;
    }
    if(m_position.y > 618) {
        m_position.y = 618;
    }
    m_shape.setPosition(m_position);
}