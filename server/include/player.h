/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** player.h
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "common.h"
    #include "map.h"
    #include "queue.h"
    #include "server.h"
    #include "teams.h"

    typedef enum orientation_s {
        NORTH = 1,
        EAST = 2,
        SOUTH = 3,
        WEST = 4,
    } orientation_t;

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
        size_t inventory[MAX_NB_RESOURCES];
        time_t last_eat_time;
        int life_units;
        time_t start_time;
        state_t state;
        char* team_name;
        command_queue_t command_queue;
    } player_t;

// ! Function prototypes:

void print_client_info(client_t* client);

void update_player(list_args_t* args, char** inputs);
bool is_team_name_valid(list_args_t* args, char** inputs);
void handle_first_client_msg(list_args_t* args, char** inputs);
void handle_client_command(list_args_t* args, char** inputs,
                           char* input_buffer);
void parse_client_input(list_args_t* args, char* received_buff);

#endif /* !PLAYER_H_ */
