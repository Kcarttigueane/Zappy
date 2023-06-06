/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** player.h
*/

#pragma once

#include "server.h"

/*
    q0 food
    q1 linemate
    q2 deraumere
    q3 sibur
    q4 mendiane
    q5 phiras
    q6 thystame
*/

typedef struct player_s {
    size_t id;
    coord_t pos;
    orientation_t orientation;
    size_t level;
    char* team_name;
    size_t inventory[MAX_NB_RESOURCES];
    size_t life_units;
    time_t last_eat_time;
    TAILQ_ENTRY(client) entries;
} player_t;
