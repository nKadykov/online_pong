#pragma once
#include <boost/asio.hpp>
#include <vector>
#include <SFML/Graphics.hpp>

struct PositionState {
    sf::Vector2f ball;
    sf::Vector2f paddle1;
    sf::Vector2f paddle2;
    int score1;
    int score2;
};

class Client {
public:
    Client(const std::string& host, unsigned short port);
    void run(const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&, const int, const int);
private:
    void read();
    void send_game_state(const PositionState& game_state);
    std::vector<char> serialize(const PositionState& game_state);
    PositionState deserialize(const std::vector<char>& data);

    boost::asio::io_context m_io_context;
    boost::asio::ip::tcp::socket m_socket;
    std::vector<char> m_buffer;
};