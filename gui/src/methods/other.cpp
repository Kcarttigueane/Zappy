/*
** EPITECH PROJECT, 2023
** gui
** File description:
** other
*/

#include "../../include/display.hpp"

void Display::checkTotalResources()
{
    size_t size = _tiles.size();
    Tile total_tile = {0, 0, 0, 0, 0, 0, 0, 0, 0.0};


    for (size_t i = 0; i < size; i++) {
        Tile tile = _tiles[i];
        total_tile.food += tile.food;
        total_tile.linemate += tile.linemate;
        total_tile.deraumere += tile.deraumere;
        total_tile.sibur += tile.sibur;
        total_tile.mendiane += tile.mendiane;
        total_tile.phiras += tile.phiras;
        total_tile.thystame += tile.thystame;
    }

    _totalFood = total_tile.food;
    _totalLinemate = total_tile.linemate;
    _totalDeraumere = total_tile.deraumere;
    _totalSibur = total_tile.sibur;
    _totalMendiane = total_tile.mendiane;
    _totalPhiras = total_tile.phiras;
    _totalThystame = total_tile.thystame;
}

