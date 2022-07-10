/*
** EPITECH PROJECT, 2022
** Snake
** File description:
** End.hpp
*/

#pragma once

#include "IGameStatus.hpp"

class End : public IGameStatus {
public:
    End();
    ~End() override;

    GameStatus ManageInput(const std::shared_ptr<sf::RenderWindow>& window) override;
    void Display(const std::shared_ptr<sf::RenderWindow>& window) override;

private:
    sf::Font _arcadeFont;

    sf::Text _endText;

    sf::SoundBuffer _buffer;
    sf::Sound _sound;
    bool _isSoundPlayed;
};