/*
** EPITECH PROJECT, 2022
** Snake - https://github.com/antoinepod/Snake
** File description:
** Game.hpp
*/

#pragma once

#include "IGameStatus.hpp"

class Game : public IGameStatus {
public:
    explicit Game(const std::shared_ptr<int>& score);
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

    sf::RectangleShape _rectangle;
    std::map<int, sf::Color> _colors;

    std::vector<std::vector<int>> _map;
    std::pair<int, int> _headPos;
    std::vector<std::pair<int, int>> _tail;
    std::pair<int, int> _direction;
    std::pair<int, int> _applePos;

    bool _isSnakeAlive;
    bool _willSnakeTurn;

    sf::Music _music;
    bool _isSoundPlayed;

    sf::SoundBuffer _buffer;
    sf::Sound _eatSound;

    sf::Sprite _apple;
    sf::Texture _appleTexture;

    std::shared_ptr<int> _score;
    sf::Text _scoreText;
    sf::Text _scoreValueText;
};

extern "C" {
    extern void cpp_srand(unsigned int seed);
}