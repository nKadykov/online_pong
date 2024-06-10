#include "ball.h"

Ball::Ball(float start_x, float start_y) {
    m_position.x = start_x;
    m_position.y = start_y;

    m_shape.setRadius(15);
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setOutlineThickness(2);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setPosition(m_position);
}

sf::FloatRect Ball::getPosition() {
    return m_shape.getGlobalBounds();
}

sf::CircleShape Ball::getShape() {
    return m_shape;
}

void Ball::bounceSides() {
    m_direction_y = -m_direction_y;
}

void Ball::bounceLeft() {
    m_position.x = 1280.0f / 2;
    m_position.y = 720.0f / 2;
    m_direction_x = -1.0;
}

void Ball::bounceRight() {
    m_position.x = 1280.0f / 2;
    m_position.y = 720.0f / 2;
    m_direction_x = -1.0;
}

void Ball::update(sf::Time dt) {
    m_position.x += m_direction_x * m_speed * dt.asSeconds();
    m_position.y += m_direction_y * m_speed * dt.asSeconds();
    m_shape.setPosition(m_position);
}

void Ball::hitBall() {
    m_direction_x = -m_direction_x;
}