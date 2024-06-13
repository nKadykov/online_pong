#include "game_client.h"
#include <iostream>
#include <cstring>

Client::Client(const std::string& host, unsigned short port)
    : m_socket(m_io_context), m_buffer(256), m_timer(m_io_context) {
    boost::asio::ip::tcp::resolver resolver(m_io_context);
    boost::asio::connect(m_socket, resolver.resolve(host, std::to_string(port)));
}

void Client::run() {
    read();
    write();
    m_io_context.run();
}

void Client::start() {
    m_is_running = true;
    m_thread = std::thread([this]() {
        run();
    });
}

void Client::stop() {
    m_is_running = false;
    m_io_context.stop();
    if(m_thread.joinable()) {
        m_thread.join();
    }
}

void Client::read() {
    boost::asio::async_read(m_socket, boost::asio::buffer(m_buffer), [this](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
            m_buffer.resize(length);
            auto game_state = deserialize(m_buffer);
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_game_state = game_state;

            }
            read();
        } else {
            m_socket.close();
        }
    });
}

void Client::write() {
    auto message = serialize(m_game_state);
    boost::asio::async_write(m_socket, boost::asio::buffer(message), [](boost::system::error_code, std::size_t) {});
    m_timer.expires_after(std::chrono::milliseconds(1));
    m_timer.async_wait([this](boost::system::error_code error_code) {
        if(!error_code) {
            write();
        }
    });
}

void Client::setGameState(const PositionState& game_state) {
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_game_state = game_state;
    }
    write();
}

PositionState Client::getGameState() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_game_state;
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