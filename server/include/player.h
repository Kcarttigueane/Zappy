/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** player.h
*/

#ifndef PLAYER_H_
#define PLAYER_H_

#include "common.h"
#include "queue.h"
#include "server.h"
#include "teams.h"

/*
    q0 food
    q1 linemate
    q2 deraumere
    q3 sibur
    q4 mendiane
    q5 phiras
    q6 thystame
*/

typedef enum orientation_s {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4,
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

typedef enum inventory_s {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} inventory_t;

typedef struct player_s {
    bool is_graphical;
    size_t id;
    coord_t pos;
    orientation_t orientation;
    size_t level;
    size_t inventory[7];
    size_t life_units;
    time_t last_eat_time;
    state_t state;
    command_queue_t command_queue;
    team_t* team;
} player_t;

// ! Function prototypes:

void print_client_info(client_t* client);

void update_player(list_args_t* args, char** inputs);
bool is_team_name_valid(list_args_t* args, char** inputs);
void handle_first_client_msg(list_args_t* args, char** inputs);
void handle_client_command(list_args_t* args, char** inputs);
void parse_client_input(list_args_t* args, char* input_buffer);

#endif /* !PLAYER_H_ */
