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

struct Egg {
    int eggNumber;
    int x;
    int y;
    int display = 1;
    int r = 225;
    int g = 225;
    int b = 225;
};

void debugTile(Tile tile);
