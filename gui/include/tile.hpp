/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** tile
*/

#pragma once

#define UP 1
#define DOWN 0

struct Tile {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    int direction;
    float offset;
};

void debugTile(Tile tile);
