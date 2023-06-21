/*
** EPITECH PROJECT, 2022
** Snake - https://github.com/antoinepod/Snake
** File description:
** End.hpp
*/

#pragma once

#include "IGameStatus.hpp"

class End : public IGameStatus {
public:
    explicit End(const std::shared_ptr<int>& score);
    ~End() override;

    GameStatus ManageInput(const std::shared_ptr<sf::RenderWindow>& window) override;
    void Display(const std::shared_ptr<sf::RenderWindow>& window) override;

private:
    std::chrono::time_point<std::chrono::system_clock> _start;
    std::chrono::duration<double> _elapsedTime{};

    sf::Font _arcadeFont;
    sf::Text _endText;
    sf::Text _scoreText;

    sf::SoundBuffer _buffer;
    sf::Sound _sound;
    bool _isSoundPlayed;

    sf::Uint8 _transparency;
    int _animationStatus;

    std::shared_ptr<int> _score;
};