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

    if (!_music.openFromFile("assets/Audio/music.ogg")) {
        std::cerr << "Failed to load 'assets/Audio/music.ogg'" << std::endl;
        exit(84);
    }
    _music.setLoop(true);
    _music.setVolume(30.f);
    _music.play();

    _gameStatus[GameStatus::MENU] = std::make_shared<Menu>();
    _gameStatus[GameStatus::GAME] = std::make_shared<Game>();
    _gameStatus[GameStatus::END] = std::make_shared<End>();
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
