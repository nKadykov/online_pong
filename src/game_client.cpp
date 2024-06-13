#include "game_client.h"
#include <iostream>
#include <cstring>

Client::Client(const std::string& host, unsigned short port)
    : m_socket(m_io_context), m_buffer(256) {
    boost::asio::ip::tcp::resolver resolver(m_io_context);
    boost::asio::connect(m_socket, resolver.resolve(host, std::to_string(port)));
}

void Client::run(const sf::Vector2f& ball_position, const sf::Vector2f& paddle1_position, const sf::Vector2f& paddle2_position, const int score_left, const int score_right) {
    read();
    m_game_state.ball = ball_position;
    m_game_state.paddle1 = paddle1_position;
    m_game_state.paddle2 = paddle2_position;
    m_game_state.score1 = score_left;
    m_game_state.score2 = score_right;
    write();
    m_io_context.run();
}

void Client::read() {
    m_socket.async_read_some(boost::asio::buffer(m_buffer), [this](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
            m_buffer.resize(length);
            auto game_state = deserialize(m_buffer);
            std::cout << "Received GameState: Ball(" << game_state.ball.x << ", " << game_state.ball.y << "), "
                      << "Platform1(" << game_state.paddle1.x << ", " << game_state.paddle1.y << "), "
                      << "Platform2(" << game_state.paddle2.x << ", " << game_state.paddle2.y << "), "
                      << "Score(" << game_state.score1 << " - " << game_state.score2 << ")" << std::endl;
            read();
        }
    });
}

void Client::write() {
    send_game_state();
    boost::asio::steady_timer timer(m_io_context);
    timer.expires_after(std::chrono::milliseconds(16));
    timer.async_wait([this](boost::system::error_code error_code) {
        if(!error_code) {
            write();
        }
    });
}

void Client::send_game_state() {
    auto message = serialize(m_game_state);
    boost::asio::async_write(m_socket, boost::asio::buffer(message), [](boost::system::error_code, std::size_t) {});
}

std::vector<char> Client::serialize(const PositionState& game_state) {
    std::vector<char> data(sizeof(PositionState));
    std::memcpy(data.data(), &game_state, sizeof(PositionState));
    return data;
}

PositionState Client::deserialize(const std::vector<char>& data) {
    PositionState game_state;
    std::memcpy(&game_state, data.data(), sizeof(PositionState));
    return game_state;
}