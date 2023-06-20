/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** setup
*/

#include "../../include/display.hpp"
#include <cmath>

#define MOD_NUMB 5

void Display::setupTiles()
{

    Tile tile = {0, 0, 0, 0, 0, 0 ,0 ,0, 0};
    for (int i = -EXTRA_TILES; i < EXTRA_TILES; i++) {
        for (int j = -EXTRA_TILES; j < EXTRA_TILES; j++) {
            _tileMovement.push_back(tile);
        }
    }
}
