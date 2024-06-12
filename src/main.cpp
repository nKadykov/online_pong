#include <iostream>
#include <boost/asio.hpp>
#include "game.h"

enum class State {GAME, GAMEOVER, MENU};

int main(int argc, char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Online pong");
    window.setFramerateLimit(60);
    sf::Event event;
    State state = State::GAME;
    Game game;

    while(window.isOpen()) {
        window.clear();
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        
        switch(state) {
            case State::GAME:
                game.start(window, argv[1], atoi(argv[2]));
                break;
        }

        window.display();
    }
}