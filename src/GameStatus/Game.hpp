/*
** EPITECH PROJECT, 2022
** Snake
** File description:
** Game.hpp
*/

#pragma once

#include "IGameStatus.hpp"

class Game : public IGameStatus {
public:
    Game();
    ~Game() override;

    GameStatus ManageInput(const std::shared_ptr<sf::RenderWindow>& window) override;
    void Display(const std::shared_ptr<sf::RenderWindow>& window) override;

    void ClearMap();
    void MoveSnake();
    void CreateApple();

private:
    std::chrono::time_point<std::chrono::system_clock> _start;
    std::chrono::duration<double> _elapsedTime{};

    sf::Font _arcadeFont;
    sf::Text _scoreText;

    sf::RectangleShape _rectangle;
    std::map<int, sf::Color> _colors;

    std::vector<std::vector<int>> _map;
    std::pair<int, int> _headPos;
    std::vector<std::pair<int, int>> _tail;
    std::pair<int, int> _direction;
    std::pair<int, int> _applePos;

    bool _isSnakeAlive;
};

extern "C" {
    extern void cpp_srand(unsigned int seed);
}