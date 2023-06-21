/*
** EPITECH PROJECT, 2022
** Snake - https://github.com/antoinepod/Snake
** File description:
** Snake.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include "GameStatus/IGameStatus.hpp"
#include "GameStatus/Menu.hpp"
#include "GameStatus/Game.hpp"
#include "GameStatus/End.hpp"

class Snake
{
private:
    std::shared_ptr<sf::RenderWindow> _window;
    GameStatus _currentGameStatus;

    std::map<GameStatus, std::shared_ptr<IGameStatus>> _gameStatus;
public:
    Snake();
    ~Snake();
    int Start();
};