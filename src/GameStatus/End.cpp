/*
** EPITECH PROJECT, 2022
** Snake - https://github.com/antoinepod/Snake
** File description:
** End.cpp
*/

#include "End.hpp"

End::End(const std::shared_ptr<int>& score) {
    if (!_buffer.loadFromFile("assets/Audio/end_sound.ogg")) {
        std::cerr << "Failed to load 'assets/Audio/end_sound.ogg'" << std::endl;
        exit(84);
    }
    _sound.setBuffer(_buffer);
    _isSoundPlayed = false;

    if (!_arcadeFont.loadFromFile("assets/Fonts/arcade_classic.ttf")) {
        std::cerr << "Failed to load 'assets/Fonts/arcade_classic.ttf'" << std::endl;
        exit(84);
    }

    _endText.setString("You    loose   !");
    _endText.setFont(_arcadeFont);
    _endText.setCharacterSize(80);
    _endText.setFillColor(sf::Color::Red);
    _endText.setPosition(710, 400);

    _scoreText.setString("SCORE        ");
    _scoreText.setFont(_arcadeFont);
    _scoreText.setCharacterSize(80);
    _scoreText.setFillColor(sf::Color::White);
    _scoreText.setPosition(730, 500);

    _transparency = 1;
    _animationStatus = 1;
    _score = score;

    _start = std::chrono::system_clock::now();
}

End::~End() = default;

GameStatus End::ManageInput(const std::shared_ptr<sf::RenderWindow> &window) {
    sf::Event event{};

    if (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return GameStatus::CLOSE;
    }
    if (_transparency <= 0)
        return GameStatus::CLOSE;

    return GameStatus::END;
}

void End::Display(const std::shared_ptr<sf::RenderWindow> &window) {
    _elapsedTime = std::chrono::system_clock::now() - _start;
    if (_elapsedTime > std::chrono::milliseconds(10)) {
        _transparency += _animationStatus;
        if (_transparency == 150)
            _animationStatus = -1;
        _start = std::chrono::system_clock::now();
    }

    sf::Color color = sf::Color::Red;
    color.a = _transparency;
    _endText.setFillColor(color);
    window->draw(_endText);

    color = sf::Color::White;
    color.a = _transparency;
    _scoreText.setFillColor(color);
    _scoreText.setString("SCORE        " + std::to_string(*_score));
    window->draw(_scoreText);

    if (!_isSoundPlayed) {
        _sound.play();
        _isSoundPlayed = true;
    }
}
