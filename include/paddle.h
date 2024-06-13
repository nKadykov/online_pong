#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
public:
    Paddle() = delete;
    Paddle(float start_x, float start_y);
    Paddle(const Paddle&) = delete;
    Paddle(Paddle&&) = delete;
    Paddle& operator=(const Paddle&) = delete;
    Paddle& operator=(Paddle&) = delete;
    ~Paddle() = default;
    
    void setPosition(const sf::Vector2f&);

    sf::RectangleShape getShape() const;
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;

    void moveDown();
    void moveUp();
    void stopDown();
    void stopUp();

    void update(sf::Time);
private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_position;
    float m_speed = 1500.0f;
    bool m_moving_down = false;
    bool m_moving_up = false;
};