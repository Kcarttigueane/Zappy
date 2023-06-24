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

void Display::checkTotalLvls()
{
    size_t size = _entities.size();
    int teamlvl[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int total = 0;

    for (size_t i = 0; i < size; i++) {
        if (int(_entities[i]._teamNumb) == _selectedTeam && _entities[i]._dead != 1) {
            teamlvl[_entities[i]._lvl - 1] += 1;
            total += 1;
        }
    }
    _teamlvl[0] = teamlvl[0];
    _teamlvl[1] = teamlvl[1];
    _teamlvl[2] = teamlvl[2];
    _teamlvl[3] = teamlvl[3];
    _teamlvl[4] = teamlvl[4];
    _teamlvl[5] = teamlvl[5];
    _teamlvl[6] = teamlvl[6];
    _teamlvl[7] = teamlvl[7];
    _teamlvl[8] = teamlvl[8];
    _teamTotalPlayers = total;
}
