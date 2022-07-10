/*
** EPITECH PROJECT, 2022
** Snake
** File description:
** Game.cpp
*/

#include <iostream>
#include "Game.hpp"

Game::Game() {
    this->ClearMap();

    _headPos = {8, 9};
    _map[_headPos.first][_headPos.second] = 2;
    std::pair<int, int> tmp;
    for (int i = 1; i < 4; ++i) {
        tmp.first = _headPos.first;
        tmp.second = _headPos.second - i;
        _map[tmp.first][tmp.second] = 3;
        _tail.push_back(tmp);
    }
    _direction = {0, 1};

    _colors[0] = sf::Color::Black;
    _colors[1] = sf::Color::White;
    _colors[2] = sf::Color::Blue;
    _colors[3] = sf::Color::Green;
    _colors[4] = sf::Color::Red;

    _start = std::chrono::system_clock::now();

    _applePos = {-1, -1};
    cpp_srand(std::time(nullptr));

    this->CreateApple();
}

Game::~Game() = default;

GameStatus Game::ManageInput(const std::shared_ptr<sf::RenderWindow> &window) {
    sf::Event event{};

    if (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return GameStatus::CLOSE;
    }
    if (sf::Keyboard::isKeyPressed(UP) && _direction.first != 1)
        _direction = {-1, 0};
    if (sf::Keyboard::isKeyPressed(DOWN) && _direction.first != -1)
        _direction = {1, 0};
    if (sf::Keyboard::isKeyPressed(LEFT) && _direction.second != 1)
        _direction = {0, -1};
    if (sf::Keyboard::isKeyPressed(RIGHT) && _direction.second != -1)
        _direction = {0, 1};

    if (sf::Keyboard::isKeyPressed(START))
        this->CreateApple();

    return GameStatus::GAME;
}

void Game::Display(const std::shared_ptr<sf::RenderWindow> &window) {
    _elapsedTime = std::chrono::system_clock::now() - _start;
    if (_elapsedTime > std::chrono::milliseconds(500)) {
        _start = std::chrono::system_clock::now();
        this->MoveSnake();
    }

    this->ClearMap();

    for (size_t i = 0; i < _map.size(); i++) {
        for (size_t j = 0; j < _map[i].size(); j++) {
            _rectangle.setSize(sf::Vector2f(32, 32));
            _rectangle.setPosition((float)j * 34 + 50, (float)i * 34 + 50);
            _rectangle.setFillColor(_colors[_map[i][j]]);
            window->draw(_rectangle);
        }
    }
}

void Game::ClearMap() {
    _map.clear();

    std::vector<int> tmp;
    for (size_t i = 0; i < 17; i++) {
        for (size_t j = 0; j < 17; j++) {
            if (i == 0 || j == 0 || i == 16 || j == 16)
                tmp.push_back(1);
            else
                tmp.push_back(0);
        }
        _map.push_back(tmp);
        tmp.clear();
    }

    for (auto & tail : _tail)
        _map[tail.first][tail.second] = 3;
    _map[_headPos.first][_headPos.second] = 2;

    if (_applePos.first != -1)
        _map[_applePos.first][_applePos.second] = 4;
}

void Game::MoveSnake() {
    if (_map[_headPos.first + _direction.first][_headPos.second + _direction.second] == 4) {
        _tail.push_back(_tail[_tail.size() - 1]);
        this->CreateApple();
    }
    for (size_t i = _tail.size() - 1; i > 0; i--) {
        _tail[i] = _tail[i - 1];
    }
    _tail[0] = _headPos;
    _headPos.first += _direction.first;
    _headPos.second += _direction.second;
}

void Game::CreateApple() {
    int x, y;
    bool status = false;

    while (!status) {
        x = std::rand() % 15 + 1;
        y = std::rand() % 15 + 1;
        if (_map[x][y] == 0) {
            _applePos = {x, y};
            status = true;
        }
    }
}
