/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** player.h
*/

#ifndef PLAYER_H_
#define PLAYER_H_

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

#define MAX_NB_RESOURCES 7

typedef enum orientation_s {
    UP_CENTER = 1,
    UP_LEFT,
    CENTER_LEFT,
    DOWN_LEFT,
    DOWN_CENTER,
    DOWN_RIGHT,
    CENTER_RIGHT,
    UP_RIGHT
} orientation_t;

typedef struct coord_s {
    int x;
    int y;
} coord_t;

typedef enum state_s {
    NONE,
    EGG,
    ACTIVE,
    DEAD,
} state_t;

typedef struct player_s {
    size_t id;
    coord_t pos;
    orientation_t orientation;
    size_t level;
    char* team_name;
    size_t inventory[MAX_NB_RESOURCES];
    size_t life_units;
    time_t last_eat_time;
    state_t state;
    char* write_buf;
    char** command_queue;
    TAILQ_ENTRY(client) entries;
} player_t;

#endif /* !PLAYER_H_ */
