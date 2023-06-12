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
    int oddeven = 1;
    for (int i = -EXTRA_TILES; i < EXTRA_TILES; i++) {
        for (int j = -EXTRA_TILES; j < EXTRA_TILES; j++) {
            if ((int(i) + EXTRA_TILES) * (EXTRA_TILES * 2 + 1) + (int(j) + EXTRA_TILES) % MOD_NUMB == 0)
                oddeven *= -1;
            tile.direction = UP;
            if (oddeven == 1)
                tile.offset = 0 + ((i % MOD_NUMB) + (j % MOD_NUMB)) * 50;
            else
                tile.offset = 0 + ((MOD_NUMB - (i % MOD_NUMB)) + (MOD_NUMB - (j % MOD_NUMB))) * 50;
            _tileMovement.push_back(tile);
        }
    }
}



// table = [[x,y] | (x,y) in your grid]
// for i
//     for j
//         table = [[np.sin(i + w*t), np.cos(j + w*t)]]

// 2pi / omega = 1 period