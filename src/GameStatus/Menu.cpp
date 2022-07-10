/*
** EPITECH PROJECT, 2022
** Snake
** File description:
** Menu.cpp
*/

#include "Menu.hpp"

Menu::Menu() {
    _start = std::chrono::system_clock::now();

    if (!_arcadeFont.loadFromFile("assets/Fonts/arcade_classic.ttf")) {
        std::cerr << "Failed to load 'assets/Fonts/arcade_classic.ttf'" << std::endl;
        exit(84);
    }

    if (!_arialFont.loadFromFile("assets/Fonts/JetBrainsMono.ttf")) {
        std::cerr << "Failed to load 'assets/Fonts/JetBrainsMono.ttf'" << std::endl;
        exit(84);
    }

    sf::FloatRect rect;

    _startText.setString("Press   a   button   to   start");
    _startText.setFont(_arcadeFont);
    _startText.setCharacterSize(40);
    _startText.setFillColor(sf::Color::White);
    rect = _startText.getLocalBounds();
    _startText.setOrigin(rect.left + rect.width / 2.0f, rect.top  + rect.height / 2.0f);
    _startText.setPosition(WINDOW_WIDTH / 2.0f, 850);

    _titleText.setString("SNAKE");
    _titleText.setFont(_arcadeFont);
    _titleText.setCharacterSize(120);
    _titleText.setFillColor(sf::Color::Green);
    rect = _titleText.getLocalBounds();
    _titleText.setOrigin(rect.left + rect.width / 2.0f, rect.top  + rect.height / 2.0f);
    _titleText.setPosition(WINDOW_WIDTH / 2.0f, 150);

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
    rect = _asciiSnake.getLocalBounds();
    _asciiSnake.setOrigin(rect.left + rect.width / 2.0f, rect.top  + rect.height / 2.0f);
    _asciiSnake.setPosition(WINDOW_WIDTH / 2.0f, 550);
}

Menu::~Menu() = default;

GameStatus Menu::ManageInput(const std::shared_ptr<sf::RenderWindow>& window) {
    sf::Event event{};

    if (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return GameStatus::CLOSE;
    }
    if (sf::Keyboard::isKeyPressed(START))
        return GameStatus::GAME;
    return GameStatus::MENU;
}

void Menu::Display(const std::shared_ptr<sf::RenderWindow> &window) {

    _elapsedTime = std::chrono::system_clock::now() - _start;
    if (_elapsedTime > std::chrono::milliseconds(500)) {
        if (_elapsedTime > std::chrono::milliseconds(1000))
            _start = std::chrono::system_clock::now();
        window->draw(_startText);
    }

    window->draw(_titleText);
    window->draw(_asciiSnake);
}
