#pragma once
#include <boost/asio.hpp>
#include <vector>
#include <thread>
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
    void run();
    void start();
    void stop();

    void setGameState(const PositionState&);
    PositionState getGameState() const;
private:
    void read();
    void write();
    std::vector<char> serialize(const PositionState&);
    PositionState deserialize(const std::vector<char>&);

    boost::asio::io_context m_io_context;
    boost::asio::ip::tcp::socket m_socket;
    std::vector<char> m_buffer;
    PositionState m_game_state;
    std::thread m_thread;
    mutable std::mutex m_mutex;
    boost::asio::steady_timer m_timer;
    bool m_is_running;
};