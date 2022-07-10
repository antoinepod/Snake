/*
** EPITECH PROJECT, 2022
** Snake
** File description:
** Main.cpp
*/

#include "Snake.hpp"

int main()
{
    std::shared_ptr<Snake> game = std::make_shared<Snake>();

    return game->Start();
}