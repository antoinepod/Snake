/*
** EPITECH PROJECT, 2022
** Snake
** File description:
** Menu.hpp
*/

#pragma once

#include <chrono>
#include "IGameStatus.hpp"

class Menu : public IGameStatus {
public:
    Menu();
    ~Menu() override;

    void Display(const std::shared_ptr<sf::RenderWindow>& window) override;
    GameStatus ManageInput(const std::shared_ptr<sf::RenderWindow>& window) override;

private:
    std::chrono::time_point<std::chrono::system_clock> _start;
    std::chrono::duration<double> _elapsedTime{};

    sf::Font _arcadeFont;
    sf::Font _arialFont;

    sf::Text _startText;
    sf::Text _titleText;
    sf::Text _asciiSnake;
};