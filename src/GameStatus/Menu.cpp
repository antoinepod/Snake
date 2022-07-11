/*
** EPITECH PROJECT, 2022
** Snake
** File description:
** Menu.cpp
*/

#include "Menu.hpp"

Menu::Menu() {
    _start = std::chrono::system_clock::now();

    if (!_startMusic.openFromFile("assets/Audio/start_sound.ogg")) {
        std::cerr << "Failed to load 'assets/Audio/start_sound.ogg'" << std::endl;
        exit(84);
    }
    _startMusic.setVolume(50.0f);
    _startMusic.play();

    if (!_arcadeFont.loadFromFile("assets/Fonts/arcade_classic.ttf")) {
        std::cerr << "Failed to load 'assets/Fonts/arcade_classic.ttf'" << std::endl;
        exit(84);
    }

    if (!_arialFont.loadFromFile("assets/Fonts/JetBrainsMono.ttf")) {
        std::cerr << "Failed to load 'assets/Fonts/JetBrainsMono.ttf'" << std::endl;
        exit(84);
    }

    _titleText.setString("SNAKE");
    _titleText.setFont(_arcadeFont);
    _titleText.setCharacterSize(120);
    _titleText.setFillColor(sf::Color::Green);
    _titleText.setPosition(795, 150);

    std::ifstream file("assets/Images/ascii_snake.txt");
    if (!file) {
        std::cerr << "Failed to load 'assets/Images/ascii_snake.ttf'" << std::endl;
        exit(84);
    }
    std::ostringstream ss;
    ss << file.rdbuf();
    _asciiSnake.setString(ss.str());
    _asciiSnake.setFont(_arialFont);
    _asciiSnake.setCharacterSize(30);
    _asciiSnake.setFillColor(sf::Color::Green);
    _asciiSnake.setPosition(620, 400);

    _transparency = 1;
    _animationStatus = 1;
}

Menu::~Menu() = default;

GameStatus Menu::ManageInput(const std::shared_ptr<sf::RenderWindow>& window) {
    sf::Event event{};

    if (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return GameStatus::CLOSE;
    }
    if (_transparency <= 0)
        return GameStatus::GAME;
    return GameStatus::MENU;
}

void Menu::Display(const std::shared_ptr<sf::RenderWindow> &window) {
    _elapsedTime = std::chrono::system_clock::now() - _start;
    if (_elapsedTime > std::chrono::milliseconds(10)) {
        _transparency += _animationStatus;
        if (_transparency == 150)
            _animationStatus = -1;
        _start = std::chrono::system_clock::now();
    }

    sf::Color color = sf::Color::Green;
    color.a = _transparency;
    _titleText.setFillColor(color);
    _asciiSnake.setFillColor(color);
    window->draw(_titleText);
    window->draw(_asciiSnake);
}
