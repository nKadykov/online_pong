#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball() = delete;
    Ball(float start_x, float start_y);
    Ball(const Ball&) = delete;
    Ball(const Ball&&) = delete;
    Ball& operator=(const Ball&) = delete;
    Ball& operator=(Ball&&) = delete;
    ~Ball() = default;

    void setPosition(const sf::Vector2f&);

    sf::FloatRect getGlobalBounds() const;
    sf::CircleShape getShape() const;
    sf::Vector2f getPosition() const;

    void bounceSides();
    void bounceLeft();
    void bounceRight();
    void hitBall();
    void update(sf::Time dt);
private:
    sf::Vector2f m_position;
    sf::CircleShape m_shape;
    float m_speed = 500;
    float m_direction_x = 1.0f;
    float m_direction_y = 1.0f;
};