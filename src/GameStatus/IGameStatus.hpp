/*
** EPITECH PROJECT, 2022
** Snake
** File description:
** IGameStatus.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#define WINDOW_WIDTH 1680
#define WINDOW_HEIGHT 1050

#define START sf::Keyboard::Key::Space
#define UP sf::Keyboard::Key::Up
#define DOWN sf::Keyboard::Key::Down
#define LEFT sf::Keyboard::Key::Left
#define RIGHT sf::Keyboard::Key::Right

enum GameStatus {
    MENU,
    GAME,
    END,
    CLOSE
};

class IGameStatus {
public:
    virtual ~IGameStatus() = default;

    virtual void Display(const std::shared_ptr<sf::RenderWindow>& window) = 0;
    virtual GameStatus ManageInput(const std::shared_ptr<sf::RenderWindow>& window) = 0;

};
