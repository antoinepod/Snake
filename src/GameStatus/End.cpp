/*
** EPITECH PROJECT, 2022
** Snake
** File description:
** End.cpp
*/

#include "End.hpp"

End::End() {
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

    _endText.setString("You    loosed   !");
    _endText.setFont(_arcadeFont);
    _endText.setCharacterSize(80);
    _endText.setFillColor(sf::Color::Red);
    sf::FloatRect rect = _endText.getLocalBounds();
    _endText.setOrigin(rect.left + rect.width / 2.0f, rect.top  + rect.height / 2.0f);
    _endText.setPosition(WINDOW_WIDTH / 2.0f, 200);
}

End::~End() = default;

GameStatus End::ManageInput(const std::shared_ptr<sf::RenderWindow> &window) {
    sf::Event event{};

    if (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return GameStatus::CLOSE;
    }

//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
//        _sound.play();
//    }

    return GameStatus::END;
}

void End::Display(const std::shared_ptr<sf::RenderWindow> &window) {
    window->draw(_endText);

    if (!_isSoundPlayed) {
        _sound.play();
        _isSoundPlayed = true;
    }
}

