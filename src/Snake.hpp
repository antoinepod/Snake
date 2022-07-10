/*
** EPITECH PROJECT, 2022
** Snake
** File description:
** Display.hpp
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

    sf::Music _music;
    std::map<GameStatus, std::shared_ptr<IGameStatus>> _gameStatus;
public:
    Snake();
    ~Snake();
    int Start();
};