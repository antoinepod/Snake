/*
** EPITECH PROJECT, 2022
** Snake - https://github.com/antoinepod/Snake
** File description:
** Game.cpp
*/

#include "Game.hpp"

Game::Game(const std::shared_ptr<int>& score) {
    if (!_music.openFromFile("assets/Audio/music.ogg")) {
        std::cerr << "Failed to load 'assets/Audio/music.ogg'" << std::endl;
        exit(84);
    }
    _music.setLoop(true);
    _music.setVolume(30.f);

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

    sf::Color headColor = {50, 150, 50, 200};
    _colors[0] = sf::Color::Black;
    _colors[1] = sf::Color::White;
    _colors[3] = headColor;
    _colors[2] = sf::Color::Green;
    _colors[4] = sf::Color::Transparent;

    _start = std::chrono::system_clock::now();

    _applePos = {-1, -1};
    cpp_srand(std::time(nullptr));

    this->CreateApple();

    _isSnakeAlive = true;
    _willSnakeTurn = false;
    _isSoundPlayed = false;

    if (!_buffer.loadFromFile("assets/Audio/eat_sound.ogg")) {
        std::cerr << "Failed to load 'assets/Audio/eat_sound.ogg'" << std::endl;
        exit(84);
    }
    _eatSound.setBuffer(_buffer);

    if (!_appleTexture.loadFromFile("assets/Images/apple.png")) {
        std::cerr << "Failed to load 'assets/Images/apple.png'" << std::endl;
        exit(84);
    }
    _apple.setTexture(_appleTexture);
    _apple.setScale(0.15f, 0.15f);

    _score = score;

    if (!_arcadeFont.loadFromFile("assets/Fonts/arcade_classic.ttf")) {
        std::cerr << "Failed to load 'assets/Fonts/arcade_classic.ttf'" << std::endl;
        exit(84);
    }

    _scoreText.setString("Score");
    _scoreText.setFont(_arcadeFont);
    _scoreText.setCharacterSize(80);
    _scoreText.setFillColor(sf::Color::White);
    _scoreText.setPosition(1550, 380);

    _scoreValueText.setString("0");
    _scoreValueText.setFont(_arcadeFont);
    _scoreValueText.setCharacterSize(80);
    _scoreValueText.setFillColor(sf::Color::White);
    _scoreValueText.setPosition(1550, 480);
}

Game::~Game() {
    if (_music.getStatus() == sf::SoundSource::Playing)
        _music.stop();
    std::cout << *_score << std::endl;
}

GameStatus Game::ManageInput(const std::shared_ptr<sf::RenderWindow> &window) {
    if (!_isSnakeAlive) {
        _music.stop();
        return GameStatus::END;
    }

    sf::Event event{};

    if (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return GameStatus::CLOSE;
        if (event.type == sf::Event::JoystickMoved) {
            if (!_willSnakeTurn) {
                float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
                float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

                if (x == 0 && y == -100 && _direction.first != 1) {
                    _direction = {-1, 0};
                    _willSnakeTurn = true;
                } if (x == 0 && y == 100 && _direction.first != -1) {
                    _direction = {1, 0};
                    _willSnakeTurn = true;
                } if (x == -100 && y == 0 && _direction.second != 1) {
                    _direction = {0, -1};
                    _willSnakeTurn = true;
                } if (x == 100 && y == 0 && _direction.second != -1) {
                    _direction = {0, 1};
                    _willSnakeTurn = true;
                }
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(START))
        this->CreateApple();

    return GameStatus::GAME;
}

void Game::Display(const std::shared_ptr<sf::RenderWindow> &window) {
    if (!_isSoundPlayed) {
        _music.play();
        _isSoundPlayed = true;
    }

    _elapsedTime = std::chrono::system_clock::now() - _start;
    if (_elapsedTime > std::chrono::milliseconds(300)) {
        _start = std::chrono::system_clock::now();
        this->MoveSnake();
    }

    this->ClearMap();

    for (size_t i = 0; i < _map.size(); i++) {
        for (size_t j = 0; j < _map[i].size(); j++) {
            _rectangle.setSize(sf::Vector2f(48, 48));
            _rectangle.setPosition((float) j * 50 + 530, (float) i * 50 + 80);
            _rectangle.setFillColor(_colors[_map[i][j]]);
            window->draw(_rectangle);
        }
    }
    _apple.setPosition((float) _applePos.second * 50 + 530, (float) _applePos.first * 50 + 80);

    window->draw(_apple);
    window->draw(_scoreText);
    _scoreValueText.setString(std::to_string(*_score));
    window->draw(_scoreValueText);
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
        _eatSound.play();
        *_score += 10;
        _tail.push_back(_tail[_tail.size() - 1]);
        this->CreateApple();
    }

    if (_map[_headPos.first + _direction.first][_headPos.second + _direction.second] == 1
        || _map[_headPos.first + _direction.first][_headPos.second + _direction.second] == 3) {
        _isSnakeAlive = false;
        return;
    }

    for (size_t i = _tail.size() - 1; i > 0; i--) {
        _tail[i] = _tail[i - 1];
    }
    _tail[0] = _headPos;
    _headPos.first += _direction.first;
    _headPos.second += _direction.second;

    _willSnakeTurn = false;
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

extern "C" {
    extern void cpp_srand(unsigned int seed) {
        return srand(seed);
    }
}
