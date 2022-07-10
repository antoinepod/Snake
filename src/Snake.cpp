/*
** EPITECH PROJECT, 2022
** Snake
** File description:
** Display.cpp
*/

#include "Snake.hpp"

Snake::Snake() {
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake");
    _currentGameStatus = GameStatus::MENU;

    if (!_music.openFromFile("assets/music.ogg")) {
        std::cerr << "Failed to load 'assets/music.ogg'" << std::endl;
        exit(84);
    }
    _music.setLoop(true);
    _music.play();

    _gameStatus[GameStatus::MENU] = std::make_shared<Menu>();
    _gameStatus[GameStatus::GAME] = std::make_shared<Game>();
}

Snake::~Snake() {
    if (_window->isOpen())
        _window->close();
    if (_music.getStatus() == sf::SoundSource::Playing)
        _music.stop();
}

int Snake::Start() {
    while(true) {
        _currentGameStatus = _gameStatus[_currentGameStatus]->ManageInput(_window);
        if (_currentGameStatus == GameStatus::CLOSE)
            break;
        _window->clear(sf::Color::Black);
        _gameStatus[_currentGameStatus]->Display(_window);
        _window->display();
    }
    return 0;
}
