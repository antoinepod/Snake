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

    std::shared_ptr<int> score = std::make_shared<int>(0);

    _gameStatus[GameStatus::MENU] = std::make_shared<Menu>();
    _gameStatus[GameStatus::GAME] = std::make_shared<Game>(score);
    _gameStatus[GameStatus::END] = std::make_shared<End>(score);
}

Snake::~Snake() {
    if (_window->isOpen())
        _window->close();
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
